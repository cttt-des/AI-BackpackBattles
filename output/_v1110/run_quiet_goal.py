"""Continue verification after the independently running full normal build."""
import time
import quiet_round as q

def main():
    started=time.monotonic()
    while not (q.p.WORK/'prototype_build.json').exists():
        if time.monotonic()-started>1800:raise TimeoutError('Normal build did not produce its receipt')
        time.sleep(3)
    q.drive()
if __name__=='__main__':main()
