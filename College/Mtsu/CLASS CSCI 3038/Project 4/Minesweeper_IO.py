# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 4: Minesweeper

import datetime

from Cell import Cell_Type
from Cell import Cell
from Field_Management import touching_count

def refresh_field(mine_field_grid, board_field):
    """Refreshes the minefield to show cleared squares."""
    for row in range(9):        
        for column in range(9):

            cell = mine_field_grid[row][column]
            cell_button = board_field[row][column]
            
            if cell.is_flagged == True:

                cell_button.config(text="| >\n|  ", bg = "#efe9f9")
                
            elif cell.is_revealed == True:
                if cell.cell_type == Cell_Type.blank:
                    cell_button.config(text="   ", bg = "#efe9f9")
                else:                        
                    
                    touching_cnt = touching_count(mine_field_grid, row, column)

                    if touching_cnt == 0:
                        touching_cnt = "   "

                    cell_button.config(text=f" {touching_cnt} ", bg = "#efe9f9")
        

def refresh_field_final(mine_field_grid, board_field):
    """Refreshes the minefield to show all squares."""
    for row in range(9):        
        for column in range(9):
            
            cell = mine_field_grid[row][column]
            cell_button = board_field[row][column]

            if cell.cell_type == Cell_Type.blank:

                cell_button.config(text="   ", bg = "#efe9f9")

            elif cell.cell_type == Cell_Type.mine:
                
                cell_button.config(text=" * ", bg = "#efe9f9")

            else:

                touching_cnt = touching_count(mine_field_grid, row, column)

                if touching_cnt == 0:
                    touching_cnt = "   "

                cell_button.config(text=f" {touching_cnt} ", bg = "#efe9f9")