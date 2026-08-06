#!/usr/bin/env python3

##  Seeking an AVL implementation that I know relatively works.


##  Note that this implementation is not perfect, and does have a few
##  quirks, but is approximately of O(logn) size upon use.

import unittest, math, random, time

from avl_implementation import AVLTree, Node


class TestAVLImplementation(unittest.TestCase):

    def setUp(self):

        ##  64 words via GPT-OSS.
        
        self.words = ["alpha","bravo","charlie","delta","echo","foxtrot","golf","hotel","india","juliet","kilo","lima","mike","november","oscar","papa","quebec","romeo","sierra","tango","uniform","victor","whiskey","xray","yankee","zulu","apex","bloom","cinder","dune","ember","frost","glade","haven","iris","jade","knoll","lagoon","mist","nebula","orbit","pinnacle","quark","rift","sable","tide","ultra","vortex","wisp","xenon","yonder","zenith","amber","briar","cobalt","dynamo","eclipse","flare","garnet","helium","ivory","jadeite","kyoto","lattice"]

        self.t = AVLTree()       

       
    def test_insert_duplicates(self):

        for w in self.words:

             self.t.insert(w)

        random.seed(564596754098679480675940)

        random.shuffle(self.words)

        ##  Attempt to insert twice.

        for w in self.words:

            self.t.insert(w)

        ##  Check that only one insert of each element occurred.

        self.assertEqual(len(self.t.inorder_traverse()),
                         len(self.words))

        ##  Check the height is not greater than log2(64).

        self.assertEqual(self.t.height,
                         math.log2(len(self.words)))


    def test_insert_all_delete_all(self):

        for w in self.words:

            self.t.insert(w)

        ##  Check elements were added successfully.
        
        self.assertEqual(len(self.t.inorder_traverse()),
                         len(self.words))
 
        self.assertEqual(self.t.height,
                         math.log2(len(self.words)))
        
        for w in self.words:

            self.t.delete(w)

        ##  Check tree is now empty.

        self.assertEqual(len(self.t.inorder_traverse()), 0)

        ##  A quirk of the implementation is that a tree with a null root node is of negative height.
 
        self.assertEqual(self.t.height, -1)
        

    def test_insert_extra(self):

        ##  For some reason you have to add at least an extra 4 to a
        ##  tree of size 64, for the height calculation to tip to >log2(64).
        
        ##  Nonetheless, this implementation seems close enough to log(n).
        
        w_extra = ["Cascade", "Nimbus", "Quasar", "Raven"]

        for w in self.words:

            self.t.insert(w)

        for w in w_extra:

            self.t.insert(w)

        ##  Check elements were added successfully.
        
        self.assertEqual(len(self.t.inorder_traverse()),
                           len(self.words) + len(w_extra))

        ##  Check the height is greater than log2(64).

        self.assertGreater(self.t.height,
                             math.log2(len(self.words)))


    def test_extensive(self):

        ##  Note that the dictionary takes ~20s to insert to the tree.

        ##  Load file contents to tree.

        str_test = "profanably"

        with open('dictionary.txt', "r") as f:
            for line in f:

                line_text = line.strip()
                self.t.insert(line_text)

                if line_text == str_test:
                    print(f"Adding {str_test}")

        ##  The size of the file is 466550 lines.
        ##  Check all elements were added successfully.

        self.assertEqual(len(self.t.inorder_traverse()),
                         466550)

        ##  Check the height is approximately as expected.

        self.assertLessEqual(self.t.height,
                             math.log2(466550) + 2)

        begin = time.time()
        
        ##  Time a lookup (using insert() with a known entry in lieu of a lookup() function).

        res = self.t.insert(str_test)

        print(res)

        ##  Note that a false result from insert() means that an
        ##  insertion *didn't* happen, which was because the string
        ##  *was* found.

        ##  This also exemplifies how easy it is to adjust a tree
        ##  insert() to a lookup() function (and you could probably
        ##  even do them via function currying etc., in the spirit of
        ##  libraries by Indian software developers!).
            
        if res == False:
            
            print(f"Found {str_test}")
        
        print(f"Lookup time: f{time.time() - begin}")
        
        
if __name__ == '__main__':
    unittest.main()
