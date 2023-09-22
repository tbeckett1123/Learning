# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys

from Triangle import triangle

def rectangular_prism(screen, color, starting_point, length, width, height, line_width):
    """Draws a rectangular prism"""    
    x, y = starting_point
    
    pygame.draw.rect(screen, color, pygame.Rect(x, y, length, height), line_width) # upper rectangle
    pygame.draw.rect(screen, color, (x + height / 2 , y + width / 2, length, height), line_width) # lower rectangle
    pygame.draw.line(screen, color, starting_point, (x + height / 2, y + width / 2), line_width) # top left corner line    
    pygame.draw.line(screen, color, (x + length, y), (x + length + height / 2, y + width / 2), line_width) # top right corner line
    pygame.draw.line(screen, color, (x + length, y + height), (x + length + height / 2, y + height + width / 2), line_width) # bottom right corner line
    pygame.draw.line(screen, color, (x, y + height), (x + height / 2, y + height + width / 2), line_width) # bottom left corner line
    
def cube(screen, color, starting_point, width, line_width):
    """Draws a cude"""
    rectangular_prism(screen, color, starting_point, width, width, width, line_width)

def triangular_trapezoidal_prism(screen, color, triangle_dimension, height, line_width):
    """Draws a triangular trapezoidal prism (not a pyramid)"""
    starting_x, starting_y, base_length, triangle_height = triangle_dimension

    starting_point = (starting_x, starting_y)
    starting_point_two = (starting_x - base_length, starting_y)
    starting_point_three = (starting_x + base_length / 2, starting_y - height)

    bottom_starting_point = (starting_x + height, starting_y + height)
    bottom_starting_point_two = (starting_x + height - base_length, starting_y + height)
    bottom_starting_point_three = (starting_x + height + base_length / 2, starting_y)

    triangle(screen, color, starting_point, base_length, triangle_height, line_width)
    triangle(screen, color, bottom_starting_point, base_length, triangle_height, line_width)

    pygame.draw.line(screen, color, starting_point, bottom_starting_point, line_width)
    pygame.draw.line(screen, color, starting_point_two, bottom_starting_point_two, line_width)
    pygame.draw.line(screen, color, starting_point_three, bottom_starting_point_three, line_width)