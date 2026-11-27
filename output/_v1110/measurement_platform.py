"""Windows topology and measurement counters, without changing power settings."""
import ctypes as ct
from ctypes import wintypes as wt
import psutil

def topology():
    class Record(ct.Structure):
        _fields_=[('mask',ct.c_size_t),('relationship',wt.DWORD),('data',ct.c_uint64*2)]
    assert ct.sizeof(Record)==32
    kernel=ct.WinDLL('kernel32',use_last_error=True);fn=kernel.GetLogicalProcessorInformation
    fn.argtypes=[ct.c_void_p,ct.POINTER(wt.DWORD)];fn.restype=wt.BOOL
    size=wt.DWORD();assert not fn(None,ct.byref(size)) and ct.get_last_error()==122
    buffer=ct.create_string_buffer(size.value);assert fn(buffer,ct.byref(size))
    rows=[]
    for offset in range(0,size.value,ct.sizeof(Record)):
        item=Record.from_buffer_copy(buffer,offset)
        if item.relationship==0:rows.append([i for i in range(ct.sizeof(ct.c_size_t)*8) if item.mask&(1<<i)])
    rows.sort(key=lambda x:x[0]);allowed=psutil.Process().cpu_affinity()
    candidates=[r for r in rows if set(r)&set(allowed)]
    assert len(candidates)>=2
    selected=next(i for i in candidates[1] if i in allowed)
    return dict(physical_core_logical_cpus=rows,allowed_logical_cpus=allowed,selected_logical_cpu=selected,
                selected_physical_core=candidates[1],selection_rule='first allowed logical CPU in second physical core, independent of speed results')

class Counters:
    def __init__(self):
        kernel=ct.WinDLL('kernel32',use_last_error=True)
        self.current=kernel.GetCurrentThread;self.current.restype=wt.HANDLE
        self.query=kernel.QueryThreadCycleTime;self.query.argtypes=[wt.HANDLE,ct.POINTER(ct.c_uint64)];self.query.restype=wt.BOOL
        self.processor=kernel.GetCurrentProcessorNumber;self.processor.restype=wt.DWORD
        self.handle=self.current()
    def cycles(self):
        value=ct.c_uint64()
        if not self.query(self.handle,ct.byref(value)):raise ct.WinError(ct.get_last_error())
        return value.value
