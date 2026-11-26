"""Estimate how CPU load changed repeated single-thread replay timings."""
import argparse
import json
import math
from pathlib import Path
import statistics


def fit(rows):
    load, elapsed = zip(*rows, strict=True)
    return statistics.linear_regression(load, elapsed)


def cross_validate(rows):
    fitted_errors, constant_errors = [], []
    for start in range(0, len(rows), 4):
        train = rows[:start] + rows[start + 4:]
        slope, intercept = fit(train)
        constant = statistics.mean(elapsed for _, elapsed in train)
        for load, elapsed in rows[start:start + 4]:
            fitted_errors.append(abs(math.expm1(slope * load + intercept - elapsed)))
            constant_errors.append(abs(math.expm1(constant - elapsed)))
    return {
        "median_absolute_relative_time_error": statistics.median(fitted_errors),
        "p90_absolute_relative_time_error": statistics.quantiles(fitted_errors, n=10, method="inclusive")[8],
        "constant_median_absolute_relative_time_error": statistics.median(constant_errors),
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("report", type=Path, help="One continuous benchmark report from --workers 1 --repeat")
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--reference-load", type=float, help="Target background CPU load for the empirical estimate")
    policy = parser.add_mutually_exclusive_group()
    policy.add_argument("--require-observed-range", action="store_true", dest="require_observed_range",
                        help="Reproduce the historical interpolation-only restriction")
    policy.add_argument("--allow-extrapolation", action="store_false", dest="require_observed_range",
                        help="Allow empirical normalization outside the observed range (default)")
    parser.set_defaults(require_observed_range=False)
    args = parser.parse_args()
    report = json.loads(args.report.read_bytes())
    samples = report.get("samples", ())
    if report["workers"] != 1 or len(samples) < 12:
        parser.error("Expected at least twelve consecutive single-thread samples")
    power_conditions = {(row["on_ac_before"], row["on_ac_after"]) for row in samples}
    if len(power_conditions) != 1 or next(iter(power_conditions))[0] != next(iter(power_conditions))[1]:
        parser.error("Use measurements with one consistent power source")
    load_key = "background_load_pct" if all(row.get("background_load_pct") is not None for row in samples) else "load_pct_after"
    loads = [row[load_key] for row in samples]
    if max(loads) == min(loads):
        parser.error("Observed CPU load did not vary")
    log_times = [math.log(row["wall_s"]) for row in samples]
    rows = list(zip(loads, log_times, strict=True))
    slope, intercept = fit(rows)
    residuals = [elapsed - (slope * load + intercept) for load, elapsed in rows]
    reference = statistics.median(loads) if args.reference_load is None else args.reference_load
    outside = not min(loads) <= reference <= max(loads)
    if outside and args.require_observed_range:
        parser.error("The reference load must fall within the observed range")
    mean_log_time = statistics.mean(log_times)
    variance = sum((elapsed - mean_log_time) ** 2 for elapsed in log_times)
    data = {
        "dll_sha256": report["dll_sha256"], "inputs_sha256": report["inputs_sha256"],
        "workers": 1, "samples": len(samples), "fights_per_sample": report["fights"],
        "load_field": load_key, "power_source_ac": samples[0]["on_ac_before"],
        "minimum_load_pct": min(loads), "maximum_load_pct": max(loads),
        "log_wall_seconds_intercept": intercept, "log_wall_seconds_per_load_point": slope,
        "r_squared_log_wall_time": 1 - sum(residual ** 2 for residual in residuals) / variance if variance else None,
        "reference_load_pct": reference,
        "reference_is_extrapolation": outside,
        "reference_distance_outside_observed_range_pct_points": max(min(loads) - reference, reference - max(loads), 0),
        "estimate_method": "log(wall_seconds) = intercept + slope * background_load_pct",
        "sample_normalization_formula": "fps_at_reference = observed_fps * exp(slope * (observed_load - reference_load))",
        "interpretation": "Empirical load-normalized estimate; coverage is reported, not a deployment gate. Code gains require paired A/B evidence.",
        "fitted_fights_per_second_at_reference_load": report["fights"] / math.exp(intercept + slope * reference),
        "fitted_wall_time_change_per_ten_load_points": math.expm1(slope * 10),
        "validation": cross_validate(rows),
        "estimated_fights_per_second_at_reference_load_by_sample": [
            report["fights"] / math.exp(elapsed + slope * (reference - load))
            for load, elapsed in rows
        ],
    }
    if "background_calibration" in report:
        data["background_calibration"] = report["background_calibration"]
    args.out.write_text(json.dumps(data, indent=2) + "\n", encoding="utf8")
    print(json.dumps(data, indent=2))


if __name__ == "__main__":
    main()
