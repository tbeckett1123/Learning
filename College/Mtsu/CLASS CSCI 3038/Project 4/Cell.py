# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 4: Minesweeper: Cell

from enum import Enum

class Cell_Type(Enum):
    """This enumeration denotes the states the cell type can be in."""
    blank = 1
    mine = 2
    touching = 3


class Cell:
    """The stores the status of the grid cell's various properties."""
    def __init__(self, row,column):
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