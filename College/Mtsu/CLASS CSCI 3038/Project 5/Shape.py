# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys
import enum

class TwoDimensionalShape(enum.Enum):    
    CIRCLE = 1    
    SQUARE = 2
    RECTANGLE = 3
    TRIANGLE = 4

class ThreeDimensionalShape(enum.Enum):    
    CUBE = 1
    CYLINDER = 2
    RECTANGLAR_PRISM = 3
    SPHREE = 4
    TRIANGLAR_TRAPEZOIDAL_PRISM = 5

correlated_shapes = {
    TwoDimensionalShape.CIRCLE: [
        ThreeDimensionalShape.CYLINDER, 
        ThreeDimensionalShape.SPHREE],
    TwoDimensionalShape.RECTANGLE: [
        ThreeDimensionalShape.CUBE,
        ThreeDimensionalShape.RECTANGLAR_PRISM
    ],
    TwoDimensionalShape.SQUARE: [
        ThreeDimensionalShape.CUBE, 
        ThreeDimensionalShape.CYLINDER,
        ThreeDimensionalShape.RECTANGLAR_PRISM,
        ThreeDimensionalShape.SPHREE,
        ThreeDimensionalShape.TRIANGLAR_TRAPEZOIDAL_PRISM],
    TwoDimensionalShape.TRIANGLE: [
        ThreeDimensionalShape.TRIANGLAR_TRAPEZOIDAL_PRISM
    ]
}

class Shape:
    """This is a container for all of the attriubtes and operations of a shape"""
    def __init__(self, shape_type, draw_shape, run_draw_shape, shape_attributes, hide):
        self.shape_type = shape_type
        self.__draw_shape = draw_shape
        self.__run_draw_shape = run_draw_shape
        self.__shape_attributes = shape_attributes
        self.__hide_shape = hide
    
    def render_shape(self):
        self.__run_draw_shape(self.__draw_shape, self.__shape_attributes)

    def __contains__(self, item):
        if type(self.shape_type) == TwoDimensionalShape:
            return item in correlated_shapes[self.shape_type]
        else:
            return False

    def __eq__(self, other):
        return other is not None and type(other.shape_type) == type(self.shape_type) and self.shape_type == self.shape_type

    def hide_shape(self):
        self.__shape_attributes.hide_shape()
        self.__hide_shape(self.__shape_attributes, "white")

class ShapeAttributes:
    def __init__(self, screen, color, line_width, x = None, y = None, width = None, height = None, radius = None, length = None, triangle_height= None):
        self.screen = screen
        self.color = color        
        self.x = x 
        self.y = y
        self.width = width
        self.height = height
        self.line_width = line_width                
        self.radius = radius                  
        self.length = length
        self.triangle_height = triangle_height

    def hide_shape(self):        
        self.color = "white"     
        self.x = 0 
        self.y = 0
        self.width = 0
        self.height = 0                        
        self.radius = 0                  
        self.length = 0
        self.triangle_height = 0

    def update_position(self, pos):
        self.x, self.y = pos

    def update_color(self, color):
        self.color = color
        