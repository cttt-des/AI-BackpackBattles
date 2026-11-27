"""Keep original fixture data and DLLs; validate the explicit correctness inverse."""
from prepare_native_assembly_membership import *
from prepare_ordering_correctness import verify_projection
from prepare_ordering_correctness import WORK
BASE=WORK/'retained_reference_src'
