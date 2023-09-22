import pygame
import sys

from VerticalPlane import *
from Triangle import *
from Shape import *
from ShapeLocationBox import *

class Box:
    def __init__(self, screen):
        self.screen = screen

        self.vplane_delta_x = 1
        self.vplane_delta_y = 2

        self.vplane_1_slope = (self.vplane_delta_x, self.vplane_delta_y)
        self.vplane_2_slope = (-self.vplane_delta_x, self.vplane_delta_y)


        self.vplanes_y = 440
        self.vplanes_x = 420
        
        self.vplane_1_starting_point = (self.vplanes_x, self.vplanes_y)
        self.vplane_2_starting_point = (self.vplanes_x + 360, self.vplanes_y - 90)
        self.line_1_starting_point = (self.vplanes_x + 275, self.vplanes_y - 140)
        self.line_2_starting_point = (self.vplanes_x + 50, self.vplanes_y - 10)

        self.vplane_1_length = 100
        self.vplane_1_height = 100

        self.vplane_2_length = 300
        self.vplane_2_height = 100
        
        self.line_width = 2
        
        self.line_1_ending_point = calculate_ending_point(self.line_1_starting_point, self.vplane_2_length, self.vplane_2_slope)                
        self.line_2_ending_point = calculate_ending_point(self.vplane_2_starting_point, self.vplane_1_length / 32, self.vplane_1_slope)

        self.vplane_1_color = "black"
        self.vplane_2_color = "black"
        self.box_lines_color = "black"
        
        self.vplane1 = vertical_plane(screen, self.vplane_1_color, self.vplane_1_starting_point, 
            self.vplane_1_length, self.vplane_1_slope, self.vplane_1_height, self.line_width)

        self.vplane2 = vertical_plane(screen, self.vplane_2_color, self.vplane_2_starting_point, 
            self.vplane_2_length, self.vplane_2_slope, self.vplane_2_height, self.line_width)

        self.box_line_1 = pygame.draw.line(screen, self.box_lines_color, self.line_1_starting_point, self.line_1_ending_point, self.line_width)
        self.box_line_2 = pygame.draw.line(screen, self.box_lines_color, self.line_1_starting_point, self.line_2_ending_point, self.line_width) 
        
        self.drop_square_attributes = ShapeAttributes(
            screen = self.screen, 
            color = "black",
            line_width = 2,
            x = self.vplanes_x + 65,
            y = self.vplanes_y - 30,
            width = 55,
            height = 55)
        self.drop_square_shape_location_box = ShapeLocationBox(self.screen, "white", (self.drop_square_attributes.x - 5 , self.drop_square_attributes.y - 5, 65, 65), self.drop_square_attributes.line_width, 
                Shape(TwoDimensionalShape.SQUARE, pygame.draw.rect, 
                    lambda drawer, attriubtes: drawer(attriubtes.screen, attriubtes.color, pygame.Rect(attriubtes.x, attriubtes.y, attriubtes.width, attriubtes.height), attriubtes.line_width),
                    self.drop_square_attributes,
                    lambda attributes, color: attributes.update_color(color)), 
            lambda mouse_point: cylinder_attributes.update_position((mouse_point[0] + 55 , mouse_point[1] + 30)))
        
        self.drop_square_shape_location_box.render_shape_location_box()        
        
        self.drop_circle_attributes = ShapeAttributes(
            screen = self.screen, 
            color = "black",
            line_width = 2,
            x = self.vplanes_x + 175,
            y = self.vplanes_y - 45,
            radius = 30)
        self.drop_circle_shape_location_box = ShapeLocationBox(self.screen, "white", 
            (self.drop_circle_attributes.x - 34, self.drop_circle_attributes.y - 34, 67, 67), self.drop_circle_attributes.line_width, 
                Shape(TwoDimensionalShape.CIRCLE, pygame.draw.circle,
                    lambda drawer, attributes: drawer(attributes.screen, attributes.color, (attributes.x, attributes.y), attributes.radius, attributes.line_width),
                    self.drop_circle_attributes,
                    lambda attributes, color: attributes.update_color(color)), 
            lambda mouse_point: cylinder_attributes.update_position((mouse_point[0] + 55 , mouse_point[1] + 30)))
        
        self.drop_circle_shape_location_box.render_shape_location_box()
        
        self.drop_triangle_attributes = ShapeAttributes(
            screen = self.screen, 
            color = "black",
            line_width = 2,
            x = self.vplanes_x + 255,
            y = self.vplanes_y - 75,
            length = 45,
            height = 50)
        self.drop_triangle_shape_location_box = ShapeLocationBox(self.screen, "white", 
            (self.drop_triangle_attributes.x - 50, self.drop_triangle_attributes.y - 55, 60, 83), self.drop_triangle_attributes.line_width, 
                Shape(TwoDimensionalShape.TRIANGLE, triangle,
                    lambda drawer, attributes: drawer(attributes.screen, attributes.color, (attributes.x, attributes.y), attributes.length, attributes.height, attributes.line_width),
                    self.drop_triangle_attributes,
                    lambda attributes, color: attributes.update_color(color)), 
            lambda mouse_point: drop_triangle_attributes.update_position((mouse_point[0] + 55 , mouse_point[1] + 30)))

        self.drop_triangle_shape_location_box.render_shape_location_box()

        # triangle(screen, self.drop_triangle_attributes.color, (self.drop_triangle_attributes.x, self.drop_triangle_attributes.y), self.drop_triangle_attributes.length, 
        #     self.drop_triangle_attributes.height, self.drop_triangle_attributes.line_width)

    def render_box(self):
        self.vplane1 = vertical_plane(self.screen, self.vplane_1_color, self.vplane_1_starting_point, 
            self.vplane_1_length, self.vplane_1_slope, self.vplane_1_height, self.line_width)

        self.vplane2 = vertical_plane(self.screen, self.vplane_2_color, self.vplane_2_starting_point, 
            self.vplane_2_length, self.vplane_2_slope, self.vplane_2_height, self.line_width)
        
        self.box_line_1 = pygame.draw.line(self.screen, self.box_lines_color, self.line_1_starting_point, self.line_1_ending_point, self.line_width)
        self.box_line_2 = pygame.draw.line(self.screen, self.box_lines_color, self.line_1_starting_point, self.line_2_ending_point, self.line_width) 

        self.drop_square_shape_location_box.render_shape_location_box()
        self.drop_circle_shape_location_box.render_shape_location_box()
        self.drop_triangle_shape_location_box.render_shape_location_box()        
        
        # triangle(self.screen, self.drop_triangle_attributes.color, (self.drop_triangle_attributes.x, self.drop_triangle_attributes.y), self.drop_triangle_attributes.length, 
        #     self.drop_triangle_attributes.height, self.drop_triangle_attributes.line_width)

    def match_shape(self, shape, mouse_point):
        hidden = False
        
        if shape.shape_type in correlated_shapes[self.drop_circle_shape_location_box.shape.shape_type] and self.drop_circle_shape_location_box.in_area(mouse_point):
            shape.hide_shape()
            hidden = True
        elif shape.shape_type in correlated_shapes[self.drop_triangle_shape_location_box.shape.shape_type] and self.drop_triangle_shape_location_box.in_area(mouse_point):
            shape.hide_shape()
            hidden = True        
        elif shape.shape_type in correlated_shapes[self.drop_square_shape_location_box.shape.shape_type] and self.drop_square_shape_location_box.in_area(mouse_point):
            shape.hide_shape()
            hidden = True
        
        return hidden




