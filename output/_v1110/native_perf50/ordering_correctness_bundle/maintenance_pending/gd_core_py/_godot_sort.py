"""Godot 3.6 SortArray port, preserving ties and comparator call order.

Source: Godot 3.6 core/sort_array.h. Copyright (c) 2014-present
Godot Engine contributors; (c) 2007-2014 Juan Linietsky, Ariel Manzur.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to
do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
"""


class _GodotSort:
    def __init__(self, array, compare):
        self.array = array
        self.compare = compare

    def median_of_3(self, a, b, c):
        if self.compare(a, b):
            if self.compare(b, c):
                return b
            elif self.compare(a, c):
                return c
            return a
        elif self.compare(a, c):
            return a
        elif self.compare(b, c):
            return c
        return b

    def push_heap(self, first, hole, top, value):
        array = self.array
        parent = (hole - 1) // 2
        while hole > top and self.compare(array[first + parent], value):
            array[first + hole] = array[first + parent]
            hole = parent
            parent = (hole - 1) // 2
        array[first + hole] = value

    def adjust_heap(self, first, hole, length, value):
        array = self.array
        top = hole
        child = 2 * hole + 2
        while child < length:
            if self.compare(array[first + child], array[first + child - 1]):
                child -= 1
            array[first + hole] = array[first + child]
            hole = child
            child = 2 * (child + 1)
        if child == length:
            array[first + hole] = array[first + child - 1]
            hole = child - 1
        self.push_heap(first, hole, top, value)

    def pop_heap(self, first, last, result, value):
        array = self.array
        array[result] = array[first]
        self.adjust_heap(first, 0, last - first, value)

    def make_heap(self, first, last):
        if last - first < 2:
            return
        length = last - first
        parent = (length - 2) // 2
        while True:
            self.adjust_heap(first, parent, length, self.array[first + parent])
            if parent == 0:
                return
            parent -= 1

    def partial_sort(self, first, last, middle):
        array = self.array
        self.make_heap(first, middle)
        for i in range(middle, last):
            if self.compare(array[i], array[first]):
                self.pop_heap(first, middle, i, array[i])
        while middle - first > 1:
            self.pop_heap(first, middle - 1, middle - 1, array[middle - 1])
            middle -= 1

    def partitioner(self, first, last, pivot):
        array = self.array
        while True:
            while self.compare(array[first], pivot):
                first += 1
            last -= 1
            while self.compare(pivot, array[last]):
                last -= 1
            if first >= last:
                return first
            array[first], array[last] = array[last], array[first]
            first += 1

    def introsort(self, first, last, depth):
        array = self.array
        while last - first > 16:
            if depth == 0:
                self.partial_sort(first, last, last)
                return
            depth -= 1
            pivot = self.median_of_3(array[first], array[first + (last - first) // 2], array[last - 1])
            cut = self.partitioner(first, last, pivot)
            self.introsort(cut, last, depth)
            last = cut

    def unguarded_linear_insert(self, last, value):
        array = self.array
        previous = last - 1
        while self.compare(value, array[previous]):
            array[last] = array[previous]
            last = previous
            previous -= 1
        array[last] = value

    def insertion_sort(self, first, last):
        array = self.array
        if first == last:
            return
        for i in range(first + 1, last):
            value = array[i]
            if self.compare(value, array[first]):
                for j in range(i, first, -1):
                    array[j] = array[j - 1]
                array[first] = value
            else:
                self.unguarded_linear_insert(i, value)

    def sort(self):
        length = len(self.array)
        if length == 0:
            return
        self.introsort(0, length, (length.bit_length() - 1) * 2)
        if length > 16:
            self.insertion_sort(0, 16)
            for i in range(16, length):
                self.unguarded_linear_insert(i, self.array[i])
        else:
            self.insertion_sort(0, length)


def sort_custom(array, compare):
    """Sort in place with the same calls and equal-key order as Godot 3.6."""
    _GodotSort(array, compare).sort()
    return array
