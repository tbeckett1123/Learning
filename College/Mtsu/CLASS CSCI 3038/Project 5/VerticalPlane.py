# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys
import math

def vertical_plane(screen, color, starting_point, length, slope, height, line_width):
    """Draws a vertical plane based on the provide parameters."""
    ending_point = calculate_ending_point(starting_point, length, slope)

    top_starting_point_x, top_starting_point_y = starting_point
    top_ending_point_x, top_ending_point_y = ending_point
    
    # bottom line       
    bottom_start = (top_starting_point_x, top_starting_point_y + height)    
    bottom_end = (top_ending_point_x, top_ending_point_y + height)

    # left line    
    left_start = starting_point
    left_end = (top_starting_point_x, top_starting_point_y + height)

    # right line
    right_start = ending_point
    right_end = (top_ending_point_x, top_ending_point_y + height)
    
    pygame.draw.line(screen, color, starting_point, ending_point, line_width) # top line    
    pygame.draw.line(screen, color, bottom_start, bottom_end, line_width) # bottom line
    pygame.draw.line(screen, color, left_start, left_end, line_width) # left line
    pygame.draw.line(screen, color, right_start, right_end, line_width) # left line

def calculate_ending_point(starting_point, length, slope):
    """Calculates the ending point of a line using the starting point, length, and slope as reference"""

    # This function will determine the the endpoint by consider a right triangle and calculating the
    # hypotenuse by using Pythagorean theorem and trigametric principles.

    # Extract the numerator and denominator from the slope tuple
    a, b = slope
    
    # Calculate the change in x using the slope and length
    # length is the sum of the 2 sides of a right triangle
    # (a / b) ** 2 is the squared length of adjacent side.
    # 1 represents the squared length of the opposite side.
    delta_x = length / math.sqrt(1 + (a / b) ** 2)
    
    # Determine if the slope is negative
    if a * b < 0:
        delta_x = -delta_x

    # Calculate the new x-coordinate for the ending point
    new_x = starting_point[0] + delta_x
    
    # Calculate the new y-coordinate for the ending point
    new_y = starting_point[1] + (a / b) * delta_x
    
    return (new_x, new_y)