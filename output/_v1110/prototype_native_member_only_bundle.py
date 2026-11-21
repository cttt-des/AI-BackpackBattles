"""Ablate frame reuse after the first combined comparison was inconclusive."""
from prototype_native_member_frame_bundle import optimize as combined
def optimize(native):return combined(native,member=True,frame=False)
