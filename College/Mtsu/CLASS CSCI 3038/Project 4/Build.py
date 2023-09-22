# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 4: Minesweeper - Build Routine

import random

from Cell import Cell_Type
from Cell import Cell

def build_mine_field(mine_field_grid):
    """Builds the mine field grid."""
    
    # add cells to grid    
    for i in range(9):
        
        row = []

        for j in range(9):
            cell = Cell(i,j)
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