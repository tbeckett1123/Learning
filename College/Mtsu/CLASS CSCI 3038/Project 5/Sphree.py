# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys

def sphree(screen, color, center, radius, width):
    """Draws a sphree (sorta)"""

    pygame.draw.circle(screen, color, center, radius, width)

    # Arc parameters
    arc_rect = pygame.Rect(center[0] - 100, center[1], radius * 2, width)  # x, y, width, height
    start_angle = 30  # Start angle in degrees
    stop_angle = 40  # Stop angle in degrees

    pygame.draw.arc(screen, color, arc_rect, start_angle, stop_angle)