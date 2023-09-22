# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 1: Minesweeper

import random
from enum import Enum
import datetime

class Cell_Type(Enum):
    """This enumeration denotes the states the cell type can be in."""
    blank = 1
    mine = 2
    touching = 3


class Cell:
    """The stores the status of the grid cell's various properties."""
    def __init__(self, row,column,parent_grid):
        self._row = row
        self._column = column
        self._is_flagged = False
        self._is_revealed = False        
        self._cell_type = Cell_Type.blank

    #region is flagged
    @property
    def is_flagged(self):
        """Indicates if the cell has been flaged as a mine.  The values should be True or False."""
        return self._is_flagged

    @is_flagged.setter
    def is_flagged(self, value):
        """Sets Flagged status for the cell. The values should be True or False."""
        self._is_flagged = value
    #end region is flagged

    #region is revealed
    @property
    def is_revealed(self):
        """Indicates if the cell has been revealed.  The values should be True or False."""
        return self._is_revealed
    
    @is_revealed.setter
    def is_revealed(self, value):
        """Sets Revealed status for the cell. The values should be True or False."""
        self._is_revealed = value
    #end region is revealed

    #region cell type
    @property
    def cell_type(self):
        """Indicates Cell Type for the cell. The values should be one of the eumerated values: Cell_Type.blank, Cell_Type.mine, or Cell_Type.touching."""
        return self._cell_type

    @cell_type.setter
    def cell_type(self, value):
        """Sets Cell Type for the cell. The values should be one of the eumerated values: Cell_Type.blank, Cell_Type.mine, or Cell_Type.touching."""
        self._cell_type = value
    #end region cell type    

    #region row
    @property
    def row(self):
        """The row of cell in the grid."""
        return self._row
    
    @row.setter
    def row(self, value):
        """Sets the row of the cell in the grid."""
        self._row = value
    #end region row

    #region column
    @property
    def column(self):
        """The column of cell in the grid."""
        return self._column
    
    @column.setter
    def column(self, value):
        """Sets the column of the cell in the grid."""
        self._column = value
    #end region column

def touching_count(mine_field_grid, row, column):
    """Returns the count of touching cells that contain a mine"""        
    
    cell = mine_field_grid[row][column]

    count = 0
    
    if cell.cell_type == Cell_Type.touching:        
        # check top row
        if cell.row == 0:
            # check top left corner
            if cell.column == 0:
                row = 0
                bottom_row = 1
                right_column = 1                    
                center_column = 0

                if mine_field_grid[row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

            # check top right corner
            elif cell.column == 8:
                row = 0
                bottom_row = 1
                left_column = 7
                center_column = 8

                if mine_field_grid[row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

            # other top row cells
            else:             
                c = int(cell.column)
                row = 0
                bottom_row = 1
                left_column = c - 1
                center_column = c
                right_column = c + 1
                
                if mine_field_grid[row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[row][right_column].cell_type == Cell_Type.mine:
                    count += 1
        # check bottom row
        elif cell.row == 8:
            # check bottom left corner
            if cell.column == 0:
                row = 8
                top_row = 7
                right_column = 1
                center_column = 0

                if mine_field_grid[row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][center_column].cell_type == Cell_Type.mine:
                    count += 1
            # check bottom right corner
            elif cell.column == 8:
                row = 8
                top_row = 7
                left_column = 7
                center_column = 8

                if mine_field_grid[row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][center_column].cell_type == Cell_Type.mine:
                    count += 1
            # other bottom row cells
            else: 
                c = int(cell.column)                        
                row = 8
                top_row = 7
                left_column = c - 1
                center_column = c
                right_column = c + 1
                
                if mine_field_grid[row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[row][right_column].cell_type == Cell_Type.mine:
                    count += 1
        # other row cells
        else:
            # check for left most column
            if cell.column == 0:
                r = int(cell.row)                                 
                top_row = r - 1
                row = r
                bottom_row = r + 1
                center_column = 0
                right_column = 1

                if mine_field_grid[top_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][center_column].cell_type == Cell_Type.mine:
                    count += 1
            # check for right most column
            elif cell.column == 8:           
                r = int(cell.row)
                top_row = r - 1
                row = r
                bottom_row = r + 1
                center_column = 8
                left_column = 7

                if mine_field_grid[top_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][center_column].cell_type == Cell_Type.mine:
                    count += 1
            # all center cells
            else:                
                r = int(cell.row)
                c = int(cell.column)
                top_row = r - 1
                row = r
                bottom_row = r + 1
                left_column = c - 1
                center_column = c
                right_column = c + 1

                if mine_field_grid[top_row][left_column].cell_type == Cell_Type.mine:
                    count += 1
                
                if mine_field_grid[top_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[top_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[row][right_column].cell_type == Cell_Type.mine:
                    count += 1
                
                if mine_field_grid[bottom_row][right_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][center_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[bottom_row][left_column].cell_type == Cell_Type.mine:
                    count += 1

                if mine_field_grid[row][left_column].cell_type == Cell_Type.mine:
                    count += 1    
                                
    return count

def build_mine_field(mine_field_grid):
    """Builds the mine field grid."""
    # add cells to grid
    
    for i in range(9):
        row = []            
        for j in range(9):            
            cell = Cell(i,j,mine_field_grid)
            row.append(cell)
    
        mine_field_grid.append(row)
    
    # place mines in mine field grid    
    mines = []
    count = 0
    while count < 10:
        mine = random.randint(0, 80)
        if mine not in mines:
            mines.append(mine)
            count += 1
    
    cell = 0
    for row in range(9):
        for column in range(9):            
            if cell in mines:
                mine_field_grid[row][column].cell_type = Cell_Type.mine
                #set surrounding cells as touching
                # top row
                if row == 0:
                    # top left corner
                    if column == 0:
                        r = 0
                        bottom_row = 1
                        right_column = 1                    
                        center_column = 0
                        
                        if mine_field_grid[r][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][center_column].cell_type = Cell_Type.touching

                    # top right corner
                    elif column == 8:
                        r = 0
                        bottom_row = 1
                        left_column = 7
                        center_column = 8

                        if mine_field_grid[r][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][left_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][left_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][center_column].cell_type = Cell_Type.touching

                    # other top row cells
                    else:
                        r = 0
                        bottom_row = 1
                        left_column = column - 1
                        center_column = column
                        right_column = column + 1
                        
                        if mine_field_grid[r][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][left_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][left_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][center_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[bottom_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[r][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][right_column].cell_type = Cell_Type.touching
                        
                # bottom row
                elif row == 8:
                    # bottom left corner
                    if column == 0:
                        r = 8
                        top_row = 7
                        right_column = 1
                        center_column = 0

                        if mine_field_grid[r][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[top_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[top_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][center_column].cell_type = Cell_Type.touching

                    # check bottom right corner
                    elif column == 8:
                        r = 8
                        top_row = 7
                        left_column = 7
                        center_column = 8

                        if mine_field_grid[r][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][left_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[top_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][left_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[top_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][center_column].cell_type = Cell_Type.touching

                    # other bottom row cells
                    else:
                        r = 8
                        top_row = 7
                        left_column = column - 1
                        center_column = column
                        right_column = column + 1
                        
                        if mine_field_grid[r][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][left_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[top_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][left_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[top_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][center_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[top_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][right_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[r][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[r][right_column].cell_type = Cell_Type.touching

                # other row cells
                else:
                    # left most column
                    if column == 0:
                        top_row = row - 1                        
                        bottom_row = row + 1
                        center_column = 0
                        right_column = 1

                        if mine_field_grid[top_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][center_column].cell_type = Cell_Type.touching

                        if mine_field_grid[top_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[row][right_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[bottom_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][right_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[bottom_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][center_column].cell_type = Cell_Type.touching

                    # right most column
                    elif column == 8:
                        top_row = row - 1                        
                        bottom_row = row + 1
                        center_column = 8
                        left_column = 7

                        if mine_field_grid[top_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][center_column].cell_type = Cell_Type.touching

                        if mine_field_grid[top_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][left_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[row][left_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[bottom_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][left_column].cell_type = Cell_Type.touching
                        
                        if mine_field_grid[bottom_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][center_column].cell_type = Cell_Type.touching

                    # all center cells
                    else:                        
                        top_row = row - 1
                        bottom_row = row + 1
                        left_column = column - 1
                        center_column = column
                        right_column = column + 1
                        
                        if mine_field_grid[top_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][left_column].cell_type = Cell_Type.touching

                        if mine_field_grid[top_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][center_column].cell_type = Cell_Type.touching

                        if mine_field_grid[top_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[top_row][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[row][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][right_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][right_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][center_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][center_column].cell_type = Cell_Type.touching

                        if mine_field_grid[bottom_row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[bottom_row][left_column].cell_type = Cell_Type.touching

                        if mine_field_grid[row][left_column].cell_type != Cell_Type.mine:
                            mine_field_grid[row][left_column].cell_type = Cell_Type.touching
            cell += 1

    return mine_field_grid

def guess(mine_field_grid, history):
    """Collects the player's guess."""
    flag = input("Enter a flag or guess (f for flag or u unflag or g for guess) ")
    while flag != "f" and flag != "u" and flag != "g":
        print("Invalid selection.")
        flag = input("Enter a flag or guess (f for flag or u unflag or g for guess) ")

    get_input = True
    while get_input:
        row = int(input("Enter the cell row "))
        if row > -1 and row < 9:
            get_input = False
        
        if get_input == True:
            print("Invalid input.")

    get_input = True
    while get_input:
        column = int(input("Enter the cell column "))
        if column > -1 and column < 9:
            get_input = False
        
        if get_input == True:
            print("Invalid input.")

    h = flag + " row " + str(row) + " column " + str(column)
    history.append(h)

    if flag == "f":
        mine_field_grid[row][column].is_flagged = True
    elif flag == "u":
        mine_field_grid[row][column].is_flagged = False
    elif mine_field_grid[row][column].cell_type == Cell_Type.mine:
        print("BANG - Game Over!")
        history.append(["BANG - Game Over!"])
        return False
    else:        
        mine_field_grid[row][column].is_revealed = True
        if mine_field_grid[row][column].cell_type != Cell_Type.touching and mine_field_grid[row][column].cell_type != Cell_Type.mine:
            call_history = []
            clear_field(mine_field_grid, row, column, call_history)
    
    return True

def clear_field(mine_field_grid, row , column, call_history):
    """Recursively clear all fields that are eligible to cleared."""
    # move through the grid till you hit touching cells
    if mine_field_grid[row][column].cell_type == Cell_Type.blank and mine_field_grid[row][column].cell_type != Cell_Type.touching  and [row, column] not in call_history:
        call_history.append([row, column])
        if row == 0:
            # top left corner
            if column == 0:
                r = 0
                bottom_row = 1
                right_column = 1                    
                center_column = 0
                
                clear_field(mine_field_grid, r, right_column, call_history)
                clear_field(mine_field_grid, bottom_row, right_column, call_history)
                clear_field(mine_field_grid, bottom_row, center_column, call_history)
            # top right corner
            elif column == 8:
                r = 0
                bottom_row = 1
                left_column = 7
                center_column = 8

                clear_field(mine_field_grid, r, left_column, call_history)                                
                clear_field(mine_field_grid, bottom_row, left_column, call_history)                
                clear_field(mine_field_grid, bottom_row, center_column, call_history)
            # other top row cells
            else:
                r = 0
                bottom_row = 1
                left_column = column - 1
                center_column = column
                right_column = column + 1

                clear_field(mine_field_grid, r, left_column, call_history)                
                clear_field(mine_field_grid, bottom_row, left_column, call_history)
                clear_field(mine_field_grid, bottom_row, center_column, call_history)
                clear_field(mine_field_grid, bottom_row, right_column, call_history)
                clear_field(mine_field_grid, r, right_column, call_history)
        # bottom row
        elif row == 8:
            # bottom left corner
            if column == 0:
                r = 8
                top_row = 7
                right_column = 1
                center_column = 0

                clear_field(mine_field_grid, r, right_column, call_history)
                clear_field(mine_field_grid, top_row, right_column, call_history)
                clear_field(mine_field_grid, top_row, center_column, call_history)
            # bottom right corner
            elif column == 8:
                r = 8
                top_row = 7
                left_column = 7
                center_column = 8

                clear_field(mine_field_grid, r, left_column, call_history)
                clear_field(mine_field_grid, top_row, left_column, call_history)
                clear_field(mine_field_grid, top_row, center_column, call_history)
            # other bottom row cells
            else:
                r = 8
                top_row = 7
                left_column = column - 1
                center_column = column
                right_column = column + 1

                clear_field(mine_field_grid, r, left_column, call_history)
                clear_field(mine_field_grid, top_row, left_column, call_history)
                clear_field(mine_field_grid, top_row, center_column, call_history)
                clear_field(mine_field_grid, top_row, right_column, call_history)
                clear_field(mine_field_grid, r, right_column, call_history)
        # other row cells
        else:
            # left most column
            if column == 0:
                top_row = row - 1                        
                bottom_row = row + 1
                center_column = 0
                right_column = 1

                clear_field(mine_field_grid, top_row, center_column, call_history)
                clear_field(mine_field_grid, top_row, right_column, call_history)
                clear_field(mine_field_grid, row, right_column, call_history)
                clear_field(mine_field_grid, bottom_row, right_column, call_history)
                clear_field(mine_field_grid, bottom_row, center_column, call_history)
            # right most column
            elif column == 8:
                top_row = row - 1                        
                bottom_row = row + 1
                center_column = 8
                left_column = 7

                clear_field(mine_field_grid, top_row, center_column, call_history)
                clear_field(mine_field_grid, top_row, left_column, call_history)
                clear_field(mine_field_grid, row, left_column, call_history)
                clear_field(mine_field_grid, bottom_row, left_column, call_history)
                clear_field(mine_field_grid, bottom_row, center_column, call_history)
            # all center cells
            else:
                top_row = row - 1
                bottom_row = row + 1
                left_column = column - 1
                center_column = column
                right_column = column + 1

                clear_field(mine_field_grid, top_row, left_column, call_history)
                clear_field(mine_field_grid, top_row, center_column, call_history)
                clear_field(mine_field_grid, top_row, right_column, call_history)
                clear_field(mine_field_grid, row, right_column, call_history)
                clear_field(mine_field_grid, bottom_row, right_column, call_history)
                clear_field(mine_field_grid, bottom_row, center_column, call_history)
                clear_field(mine_field_grid, bottom_row, left_column, call_history)
                clear_field(mine_field_grid, row, left_column, call_history)

    if mine_field_grid[row][column].is_flagged == False and mine_field_grid[row][column].cell_type != Cell_Type.mine:
        mine_field_grid[row][column].is_revealed = True

def print_grid(mine_field_grid):
    """Displays the minefield grid to std out."""
    count = 10

    for row in range(9):
        for column in range(9):
            if mine_field_grid[row][column].is_flagged == True:
                count = count - 1

    print(f"Mines left: {count}")
    print("  0 1 2 3 4 5 6 7 8")
    for row in range(9):
        print(f"{row} ", end="")
        for column in range(9):            
            if mine_field_grid[row][column].is_flagged == True:
                print("^ ", end="")
            elif mine_field_grid[row][column].is_revealed == True:
                if mine_field_grid[row][column].cell_type == Cell_Type.blank:
                    print("  ", end="")
                else:                        
                    print(f"{touching_count(mine_field_grid, row, column)} ", end="")
            else:
                print("x ", end="")
        print(" ")

def print_grid_final(mine_field_grid):
    """Displays the revealed minefield grid to std out."""
    print("  0 1 2 3 4 5 6 7 8")
    for row in range(9):
        print(f"{row} ", end="")
        for column in range(9):
            if mine_field_grid[row][column].cell_type == Cell_Type.blank:
                print("  ", end="")
            elif mine_field_grid[row][column].cell_type == Cell_Type.mine:
                print("^ ", end="")
            else:
                print(f"{touching_count(mine_field_grid, row, column)} ", end="")
        print(" ")

def check_for_final_conditions(mine_field_grid, history):
    """Validates user inputs for winning conditions"""
    mines_cleared = 0
    spaces_cleared = 0
    false_flags = 0
    for row in range(9):
        for column in range(9):
            if mine_field_grid[row][column].cell_type == Cell_Type.mine and mine_field_grid[row][column].is_flagged == True:
                mines_cleared += 1
            elif mine_field_grid[row][column].cell_type != Cell_Type.mine and mine_field_grid[row][column].is_flagged == True:
                false_flags += 1
            elif mine_field_grid[row][column].cell_type != Cell_Type.mine and mine_field_grid[row][column].is_revealed == True:
                spaces_cleared += 1

    winner = (spaces_cleared == 71 or mines_cleared == 10) and false_flags == 0

    if winner == True:
        print("Winner! Winner! Chicken dinner!")
        history.append("Winner! Winner! Chicken dinner!")

    # flip the bool for the return value.
    return winner == False 

def write_file(mine_field_grid, history):
    """Writes the board and player actions to a file called play_by_play_date_time.txt"""
    str_builder = "  0 1 2 3 4 5 6 7 8\n"
    for row in range(9):
        str_builder += str(row) + " "
        for column in range(9):
            if mine_field_grid[row][column].cell_type == Cell_Type.blank:
                str_builder += "  "
            elif mine_field_grid[row][column].cell_type == Cell_Type.mine:
                str_builder += "* "
            else:
                str_builder += f"{touching_count(mine_field_grid, row, column)} "
        
        str_builder += "\n"  # Move the newline character outside the inner loop

    for action in history:
        str_builder += str(action) + "\n"

    current_time = datetime.datetime.now().strftime("%H_%M_%S")        
    file_name = "play_by_play_date_time_" + current_time + ".txt"

    with open(file_name, "w") as file:    
        file.write(str_builder)
    

def main():    
    """Play mine sweeper."""     
    history = []
    mine_field_grid = []
    loop = True

    mine_field_grid = build_mine_field(mine_field_grid)

    for row in range(9):
        for column in range(9):
            print(f"{row} {column} {mine_field_grid[row][column].cell_type} {mine_field_grid[row][column].is_flagged}")

    while loop == True:
        print_grid(mine_field_grid)

        loop = guess(mine_field_grid, history)
        
        if loop == True:
            loop = check_for_final_conditions(mine_field_grid, history)

    print_grid_final(mine_field_grid)
    write_file(mine_field_grid, history)

main()