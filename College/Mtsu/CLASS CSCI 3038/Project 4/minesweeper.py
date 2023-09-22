# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 4: Minesweeper

import tkinter as tk
from Board import *

def main():    
    running = False
    window = tk.Tk()
    b = Board(window, running)
    window.mainloop()
    
main()