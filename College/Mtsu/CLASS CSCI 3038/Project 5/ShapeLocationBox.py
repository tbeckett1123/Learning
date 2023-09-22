# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 5: pygame - shape sorting game for demonstration

import pygame
import sys

from Shape import *

class ShapeLocationBox:
    def __init__(self, screen, color, rectangle_starting_point, line_width, shape, update_shape_location):
        self.screen = screen
        self.go_go_go = False
        self.color = color

        self.x, self.y, self.__height, self.__width = rectangle_starting_point    
        self.__line_width = line_width
        
        self.shape = shape
        self.update_shape_location = update_shape_location

        self.rectangle = pygame.Rect(self.x, self.y, self.__width, self.__height)

        self.shape.render_shape()        
        pygame.draw.rect(self.screen, self.color, self.rectangle)
    
    def render_shape_location_box(self):
        self.shape.render_shape()        
        pygame.draw.rect(self.screen, self.color, self.rectangle, self.__line_width)

    def update_location(self, mouse_point):
        mouse_x, mouse_y = mouse_point

        if self.go_go_go:
            dx = mouse_x - self.x
            dy = mouse_y - self.y

            new_x = self.x + dx
            new_y = self.y + dy

            if new_x >= 0 and new_x + self.__width <= self.screen.get_width():
                self.x = new_x

            if new_y >= 0 and new_y + self.__height <= self.screen.get_height():
                self.y = new_y

            self.update_shape_location(mouse_point)   
            self.rectangle = pygame.Rect(self.x, self.y, self.__width, self.__height)
    
        self.render_shape_location_box()

    def hide_shape_location_box(self):
        self.shape.hide_shape()
        self.x = 0
        self.y = 0
        self.__width = 0
        self.__height = 0
        self.rectangle = pygame.Rect(self.x, self.y, self.__width, self.__height)

    def in_area(self, mouse_point):
        mouse_x, mouse_y = mouse_point

        self.go_go_go = self.rectangle.collidepoint(mouse_x, mouse_y)
        
        return self.go_go_go