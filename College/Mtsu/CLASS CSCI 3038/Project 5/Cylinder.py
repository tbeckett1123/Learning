# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys

def cylinder(screen, color, front_center, radius, height, line_width):
    """Draws a cylinder"""
    pygame.draw.circle(screen, color, front_center, radius, line_width) # front

    front_x, front_y = front_center
    pygame.draw.circle(screen, color, (front_x - height, front_y), radius, line_width) # back

    pygame.draw.line(screen, color, (front_x, front_y + radius - 1), (front_x - height, front_y + radius - 1), line_width) # bottom line
    pygame.draw.line(screen, color, (front_x, front_y - radius + 1), (front_x - height, front_y - radius + 1), line_width) # top line
