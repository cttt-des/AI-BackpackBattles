# -*- coding: utf-8 -*-
"""Godot 3.x smaz 反向词典（Smaz_rcb[254]，来自 thirdparty/misc/smaz.c）"""
RCB = [
 " ", "the", "e", "t", "a", "of", "o", "and", "i", "n", "s", "e ", "r", " th",
 " t", "in", "he", "th", "h", "he ", "to", "\r\n", "l", "s ", "d", " a", "an",
 "er", "c", " o", "d ", "on", " of", "re", "of ", "t ", ", ", "is", "u", "at",
 "   ", "n ", "or", "which", "f", "m", "as", "it", "that", "\n", "was", "en",
 "  ", " w", "es", " an", " i", "\r", "f ", "g", "p", "nd", " s", "nd ", "ed ",
 "w", "ed", "http://", "for", "te", "ing", "y ", "The", " c", "ti", "r ", "his",
 "st", " in", "ar", "nt", ",", " to", "y", "ng", " h", "with", "le", "al", "to ",
 "b", "ou", "be", "were", " b", "se", "o ", "ent", "ha", "ng ", "their", "\"",
 "hi", "from", " f", "in ", "de", "ion", "me", "v", ".", "ve", "all", "re ",
 "ri", "ro", "is ", "co", "f t", "are", "ea", ". ", "her", " m", "er ", " p",
 "es ", "by", "they", "di", "ra", "ic", "not", "s, ", "d t", "at ", "ce", "la",
 "h ", "ne", "as ", "tio", "on ", "n t", "io", "we", " a ", "om", ", a", "s o",
 "ur", "li", "ll", "ch", "had", "this", "e t", "g ", "e\r\n", " wh", "ere",
 " co", "e o", "a ", "us", " d", "ss", "\n\r\n", "\r\n\r", "=\"", " be", " e",
 "s a", "ma", "one", "t t", "or ", "but", "el", "so", "l ", "e s", "s,", "no",
 "ter", " wa", "iv", "ho", "e a", " r", "hat", "s t", "ns", "ch ", "wh", "tr",
 "ut", "/", "have", "ly ", "ta", " ha", " on", "tha", "-", " l", "ati", "en ",
 "pe", " re", "there", "ass", "si", " fo", "wa", "ec", "our", "who", "its", "z",
 "fo", "rs", ">", "ot", "un", "<", "im", "th ", "nc", "ate", "><", "ver", "ad",
 " we", "ly", "ee", " n", "id", " cl", "ac", "il", "</", "rt", " wi", "div",
 "e, ", " it", "whi", " ma", "ge", "x", "e c", "men", ".com",
]

def smaz_decompress(data):
    out = bytearray()
    i = 0
    n = len(data)
    while i < n:
        c = data[i]
        if c == 254:               # 单字节原文
            if i + 1 < n:
                out.append(data[i+1])
            i += 2
        elif c == 255:             # 原文串
            ln = data[i+1] + 1
            out += data[i+2:i+2+ln]
            i += 2 + ln
        else:                      # 词典码
            out += RCB[c].encode('utf-8')
            i += 1
    return bytes(out)
