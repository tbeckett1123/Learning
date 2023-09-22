# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys

def triangle(screen, color, starting_point, base_length, height, line_width):
    """Draws a triangle"""
    x, y = starting_point
    top_point = (x + base_length / 2, y - height)

    pygame.draw.line(screen, color, starting_point, (x - base_length, y), line_width) 
    pygame.draw.line(screen, color, starting_point, top_point, line_width)
    pygame.draw.line(screen, color, (x - base_length, y), top_point, line_width)


