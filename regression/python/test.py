#!/usr/bin/env python

import unittest, subprocess

# path app
app = "srun -n 2 ${CMAKE_BINARY_DIR}/main/main"

class TestUM(unittest.TestCase):
 
    def test_numbers_3_4(self):
        self.assertEqual( 3*4, 12)
 
    def test_read(self):
        with open("test.dat") as f:
            content = f.readlines()
            f.close()
        v = []
        for voltage in content:
            v.append(float(voltage.split()[1])) #get col one

        w = [1.1,2.2,3.3] 

        for a, b in zip(v, w):
            self.assertAlmostEqual(a, b)
 
    def test_out(self):
        p = subprocess.Popen([app], shell=True)
        pass

 
    def test_double(self):
        a = 1.23456789
        b = 1.23456788
        self.assertAlmostEqual(a, b, places=7, msg="pb")  

if __name__ == '__main__':
    unittest.main()
