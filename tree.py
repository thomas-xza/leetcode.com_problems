#!/usr/bin/env python3

from collections import defaultdict


def tree():

    ##  Not sure exactly how to type hint this.
    
    return defaultdict(tree)


def main():

    words = ["Eclipse","Nimbus","Quill","Cascade","Velvet","Orbit","Mosaic","Harbor","Luminous","Paradox","Silhouette","Bramble","Echo","Zenith","Tide","Aurora","Cinder","Gleam","Frost","Wander"]

    t = tree()

    for w in words:

        t = insert(t, w)


def insert(t: tree, w: str):

    if t == None:
        t[0] = tree()
        t[1] = tree()

    print(t)
        

main()
