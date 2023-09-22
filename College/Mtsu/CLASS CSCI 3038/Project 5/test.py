# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys

from Cylinder import *
from VerticalPlane import *
from Prism import *
from Triangle import *
from Shape import *
from Box import *

# Initialize Pygame
pygame.init()

# Set up the display
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Draw Arc")

# Circle properties
circle_radius = 100
circle_position = (width // 2, height // 2)

circle_radius2 = 100
circle_position2 = (width // 2 + 50, height // 2 + 50)

circle_radius3 = 200
circle_position3 = (width // 2 + 75, height // 2 + 75)

# Colors
white = (255, 255, 255)
black = (0, 0, 0)
blue = (0, 0, 255)

# Arc parameters
arc_rect = pygame.Rect(200, 150, 400, 20)  # x, y, width, height
start_angle = 30  # Start angle in degrees
stop_angle = 40  # Stop angle in degrees
line_width = 3

# Ellipse parameters
ellipse_rect = pygame.Rect(200, 150, 400, 300)  # x, y, width, height
line_width = 3

# Colors
white = (255, 255, 255)
black = (0, 0, 0)
green = (0, 255, 0)

# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Clear the screen
    screen.fill(white)

    # Draw the arc
    # pygame.draw.arc(screen, black, arc_rect, start_angle, stop_angle, line_width)
    # pygame.draw.arc(screen, blue, (arc_rect[0] + 150, arc_rect[1], arc_rect[2], arc_rect[3]), start_angle, stop_angle)

    # Draw the ellipse
    # pygame.draw.ellipse(screen, black, ellipse_rect, line_width)
    # pygame.draw.ellipse(screen, green, (ellipse_rect[0] + 150, ellipse_rect[1], ellipse_rect[2], ellipse_rect[3]))

    # pygame.draw.circle(screen, (0, 0, 255), circle_position, circle_radius, 2)

    # vertical_plane(screen, (280, 100), 100, (-1,2), 100, "red", 2)
    # vertical_plane(screen, (100, 100), 100, (1,2), 100, "blue", 2)

    # rectangular_prism(screen, (300, 50), 200, 300, 100, "black", 2)
    cube(screen, "green", (200, 200), 100, 2)

    # cylinder(screen, "red", circle_position, circle_radius, 100, 2)
    # cylinder(screen, "blue", circle_position2, circle_radius2, 500, 2)
    # cylinder(screen, "green", circle_position3, circle_radius3, 25, 2)

    # triangle(screen, "red", (200, 200), 100, 100, 2)
    # triangular_trapezoidal_prism(screen, "red", (200, 200, 100, 100), 100, 2)

    # cylinder_container = Shape(ThreeDimensionalShape.CYLINDER, cylinder, lambda drawer: drawer(screen, "red", circle_position, circle_radius, 100, 2))
    # cylinder_container.render_shape()

    # pygame.draw.rect(screen, "red", (100, 100, 200, 200), 2)
    # square_container = Shape(TwoDimensionalShape.SQUARE, pygame.draw.rect, lambda drawer: drawer(screen, "red", (100, 100, 200, 200), 2))
    # square_container.render_shape()

    box = Box(screen)

    pygame.display.flip()

# Clean up
pygame.quit()
sys.exit()