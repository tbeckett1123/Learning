# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 4: Minesweeper

from Cell import Cell_Type
from Cell import Cell

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


def check_for_final_conditions(mine_field_grid):
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
    
    return winner 