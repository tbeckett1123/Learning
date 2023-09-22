# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 4: Minesweeper

import tkinter as tk
import threading
import time

from Cell import Cell_Type
from Cell import Cell
from Build import build_mine_field
from Field_Management import *
from Modal import Modal
from Minesweeper_IO import *

def format_time(elapsed_time):   
        
    minutes, seconds = divmod(int(elapsed_time), 60)
    
    hours, minutes = divmod(minutes, 60)
    
    return f"{hours:02d}:{minutes:02d}:{seconds:02d}"

class Board:
    """Board Management Functions"""
    def __init__(self, window, running):
        self.window = window
        
        self.window.title("Minesweeper")
        self.game_over = False
        
        self.window_width = 385        
        self.window_height = 370
        self.window.geometry(f"{self.window_width}x{self.window_height}")
        self.window.resizable(False, False)

        self.top_frame = tk.Frame(self.window, borderwidth = 2, relief = tk.GROOVE, width = self.window_width, height = self.window_height * .10)
        self.top_frame.pack(side = tk.TOP, padx = 1, pady = 1, fill = tk.BOTH, expand = True)

        self.top_left_frame = tk.Frame(self.top_frame, borderwidth = 0, width = self.window_width * .3, height = self.window_height * .09)
        self.top_left_frame.pack(side = tk.LEFT)
        self.reset_button = tk.Button(self.top_left_frame, text = "Reset")
        self.reset_button.bind("<Button-1>", lambda event: reset_click(event, self))
        self.reset_button.pack(side = tk.LEFT, padx = 1, pady = 1)
        
        # stopwatch
        self.top_right_frame = tk.Frame(self.top_frame, borderwidth = 0, width = self.window_width * .3, height = self.window_height * .09)
        self.top_right_frame.pack(side = tk.RIGHT)
        self.start_time = None
        self.time_var = tk.StringVar()
        self.time_var.set("00:00:00")
        self.display_label = tk.Label(self.top_right_frame, borderwidth = 2, text = "00:00:00", textvariable=self.time_var, font=("Arial", 10))
        self.display_label.pack(side = tk.RIGHT, padx=1, pady=1)
        
        #self.stop_watch = Stopwatch(window, self.display_label, self.time_var)

        self.bottom_frame = tk.Frame(self.window, borderwidth = 2, relief = tk.GROOVE, width = self.window_width, height = self.window_height * .90)
        self.bottom_frame.pack(side = tk.BOTTOM, padx = 1, pady = 1, fill = tk.BOTH, expand = True)

        self.mine_field_grid = []
        self.mine_field_grid = build_mine_field(self.mine_field_grid)
        self.board_field = self.set_field()
        
        self.running = running       
        self.thread = None
         
        self.window.bind('<Escape>', lambda e: on_close(self.window, self) or window.destroy())

    def start_timer(self):
        if self.running == False and self.game_over == False:
            self.start_time = time.time()
            self.running = True
            self.thread = threading.Thread(daemon = True, target = update_time, args = (self.window, self.running, self.start_time, self.time_var, self.display_label, self))                      
            self.thread.start()

    def set_field(self):
        """Draws the draws the mine field grid for the game"""
        buttons = []
        for row in range(9):
            row_buttons = []
            for col in range(9):
                button = tk.Button(self.bottom_frame, text="  ", width=2, height=2)
                button.grid(row=row, column=col)
                button.bind("<Button-1>", lambda event, r=row, c=col: button_click(event, r, c, self))
                button.bind("<Button-3>", lambda event, r=row, c=col: alt_button_click(event, r, c, self))
                row_buttons.append(button)
            buttons.append(row_buttons)
        return buttons

def button_click(event, r, c, b):
    cell = b.mine_field_grid[r][c]
    cell_button = b.board_field[r][c]

    # if it's flagged or already revealed do nothing
    if cell.is_flagged == False and cell.is_revealed == False and b.game_over == False:

        cell.is_revealed = True

        if cell.cell_type == Cell_Type.mine:           

            b.running = False
            b.thread.join()

            refresh_field_final(b.mine_field_grid, b.board_field)

            m = Modal(b.window, "Game Over", "You lost. Better luck next time.", 90, 250)

            b.game_over = True

        else:
            touching_cnt = touching_count(b.mine_field_grid, r, c)
            
            if touching_cnt == 0:
                touching_cnt = "   "

            cell_button.config(text=f" {touching_cnt} ", bg = "#efe9f9")

            winner = check_for_final_conditions_event(r, c, b)

            if winner == False:

                call_history = []
                clear_field(b.mine_field_grid, r, c, call_history)
                refresh_field(b.mine_field_grid, b.board_field)
                check_for_final_conditions_event(r, c, b)

    b.start_timer()

def check_for_final_conditions_event(r, c, b):
    winner = check_for_final_conditions(b.mine_field_grid)
    
    if winner == True:                

        b.running = False
        b.thread.join()

        refresh_field_final(b.mine_field_grid, b.board_field)
        
        m = Modal(b.window, "Game Over", "Winner! Winnner! Chicken Dinner!", 90, 300)                
        
        b.game_over = True
    
    return winner

def alt_button_click(event, r, c, b):    
    cell = b.mine_field_grid[r][c]
    cell_button = b.board_field[r][c]

    # if the cell is reveal do nothing
    if cell.is_revealed == False and b.game_over == False:
        if cell.is_flagged == True:
            cell_button.config(text="  ")
            cell.is_flagged = False
        else:
            cell_button.config(text=f"| >\n|  ")
            cell.is_flagged = True

    b.start_timer()

def reset_stopwatch(board):
    
    if board.running == True:
        board.running = False        
        board.thread.join(timeout=0.05)
    
    board.game_over = False    
    board.start_time = None    
    board.time_var.set("00:00:00")
    board.display_label.config(text=board.time_var)

def reset_click(event, b):
    reset_stopwatch(b)

    b.mine_field_grid = []
    b.mine_field_grid = build_mine_field(b.mine_field_grid)
    b.board_field = b.set_field()    

def on_close(window, b):
    if b.running == True:
        b.running = False
        b.thread.join(timeout=0.05)
    
def update_time(window, running, start_time, time_var, display_label, b):
    while b.running == True:
        
        if start_time is None:
            start_time = time.time()

        elapsed_time = time.time() - start_time

        formatted_time = format_time(elapsed_time)
        
        time_var.set(formatted_time)

        display_label.config(text=time_var)

        time.sleep(1)
