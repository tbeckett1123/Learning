# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys

from Box import *
from Cylinder import *
from Shape import *
from ShapeLocationBox import *
from Prism import *

def create_cylinder(screen):
    cylinder_attributes = ShapeAttributes(screen = screen, color = "blue", x = 250, y = 250, radius = 25, height = 25, line_width = 2)       
    
    cylinder_container = ShapeLocationBox(screen,
        "white", 
        (195, 220, 60, 85), 2, 
        Shape(ThreeDimensionalShape.CYLINDER, 
            cylinder, 
            lambda drawer, attributes: drawer(attributes.screen, attributes.color, (attributes.x, attributes.y), attributes.radius, attributes.height, attributes.line_width), 
            cylinder_attributes,
            lambda attributes, color: attributes.update_color(color)),
        lambda mouse_point: cylinder_attributes.update_position((mouse_point[0] + 55 , mouse_point[1] + 30)))

    return (cylinder_attributes, cylinder_container)

def create_cude(screen):
    cube_attributes = ShapeAttributes(screen = screen, color = "blue", x = 100, y = 100, width = 50, line_width = 2)
    
    cube_container = ShapeLocationBox(screen, 
        "white",
        (97, 97, 83, 83), 2,
        Shape(ThreeDimensionalShape.CUBE,
            cube,
            lambda drawer, attributes: drawer(attributes.screen, attributes.color, (attributes.x, attributes.y), attributes.width, attributes.line_width),
            cube_attributes,
            lambda attributes, color: attributes.update_color(color)),
        lambda mouse_point: cube_attributes.update_position((mouse_point[0] + 5 , mouse_point[1] + 5)))
    
    return (cube_attributes, cube_container)    

def create_prism(screen):
    prism_attributes = ShapeAttributes(screen = screen, color = "blue", x = 50, y = 400, length = 50, width = 150, height = 50, line_width = 2)
    
    prism_container = ShapeLocationBox(screen, 
        "white",
        (47, 397, 130, 83), 2,
        Shape(ThreeDimensionalShape.RECTANGLAR_PRISM,
            rectangular_prism, 
            lambda drawer, attributes: drawer(attributes.screen, attributes.color, (attributes.x, attributes.y), attributes.length, attributes.width, attributes.height, attributes.line_width),
            prism_attributes,
            lambda attributes, color: attributes.update_color(color)),
        lambda mouse_point: prism_attributes.update_position((mouse_point[0] + 3, mouse_point[1] + 3)))
    
    return (prism_attributes, prism_container)

#triangular_trapezoidal_prism(screen, color, triangle_dimension, height, line_width)

def create_triangular_trapezoidal_prism(screen):
    triangular_trapezoidal_prism_attributes = ShapeAttributes(screen = screen, color = "blue", x = 550, y = 80, length = 45, triangle_height = 50,  height = 50, line_width = 2)
    
    triangular_trapezoidal_prism_container = ShapeLocationBox(screen, 
        "white",
        (500, 28, 108, 126), 2,
        Shape(ThreeDimensionalShape.TRIANGLAR_TRAPEZOIDAL_PRISM,
            triangular_trapezoidal_prism, 
            lambda drawer, attributes: drawer(attributes.screen, attributes.color, (attributes.x, attributes.y, attributes.length, attributes.triangle_height), 
                attributes.height, attributes.line_width),
            triangular_trapezoidal_prism_attributes,
            lambda attributes, color: attributes.update_color(color)),
        lambda mouse_point: triangular_trapezoidal_prism_attributes.update_position((mouse_point[0] + 50, mouse_point[1] + 54)))
    
    return (triangular_trapezoidal_prism_attributes, triangular_trapezoidal_prism_container)

def reset_button(screen, font):

    text_to_display = "Reset"
    text_surface = font.render(text_to_display, True, "black")

    button = pygame.Rect(5, 5, 100, 30)

    pygame.draw.rect(screen, "black", (6, 6, 100, 30))
    pygame.draw.rect(screen, "grey", button)
    screen.blit(text_surface, (20, 8))

    return button

def main():

    pygame.init()

    font = pygame.font.Font(None, 36)

    width, height = 800, 600
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption("Shape Shorting Game")
    
    box = Box(screen)
    cylinder_attributes, cylinder_container = create_cylinder(screen)
    cube_attributes, cube_container = create_cude(screen)
    prism_attributes, prism_container = create_prism(screen)
    triangular_trapezoidal_prism_attributes, triangular_trapezoidal_prism_container = create_triangular_trapezoidal_prism(screen)
    
    button = reset_button(screen, font)

    tracking = False
    tracking_position = (0, 0)
    tracking_count = 0    
    tracking_object = None
    running = True
    while running:

        # Clear the screen
        screen.fill("white")

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                tracking = True
                
                mouse_x, mouse_y = event.pos
                point = pygame.mouse.get_pos()

                if cylinder_container.in_area(point) and tracking_count == 0:
                    tracking_count = 1
                    tracking_object = cylinder_container
                elif cube_container.in_area(point) and tracking_count == 0:
                    tracking_count = 1
                    tracking_object = cube_container
                elif prism_container.in_area(point) and tracking_count == 0:
                    tracking_count = 1
                    tracking_object = prism_container
                elif triangular_trapezoidal_prism_container.in_area(point) and tracking_count == 0:
                    tracking_count = 1
                    tracking_object = triangular_trapezoidal_prism_container

            elif event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                point = pygame.mouse.get_pos()
                
                if button.collidepoint(point):
                    box = Box(screen)
                    
                    cylinder_attributes, cylinder_container = create_cylinder(screen)
                    cube_attributes, cube_container = create_cude(screen)
                    prism_attributes, prism_container = create_prism(screen)
                    triangular_trapezoidal_prism_attributes, triangular_trapezoidal_prism_container = create_triangular_trapezoidal_prism(screen)
                    
                    tracking = False
                    tracking_position = (0, 0)
                    tracking_count = 0    
                    tracking_object = None
                elif tracking_object is not None:
                    hidden = box.match_shape(tracking_object.shape, point)
                
                    if hidden:
                        tracking_object.hide_shape_location_box()

                    tracking = False
                    tracking_count = 0                
                    tracking_object.go_go_go = False 
                    tracking_object = None
              
                
        if tracking == True and tracking_object is not None:
            tracking_position = pygame.mouse.get_pos()
            tracking_object.update_location(tracking_position)
        
        cylinder_container.render_shape_location_box()
        cube_container.render_shape_location_box()
        prism_container.render_shape_location_box()
        triangular_trapezoidal_prism_container.render_shape_location_box()
        button = reset_button(screen, font)
        box.render_box()    

        pygame.display.flip()

    pygame.quit()
    sys.exit()

main()