# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 2: Card Game: Card class
import enum

UNICODE_HEART = "\u2665"     # Heart: ♥
UNICODE_DIAMOND = "\u2666"   # Diamond: ♦
UNICODE_SPADE = "\u2660"     # Spade: ♠
UNICODE_CLUB = "\u2663"      # Club: ♣

class Card_Type(enum.Enum):
    """Defines valid card types: HEART, DIAMOND, SPADE, CLUB"""
    HEART = 1
    DIAMOND = 2
    SPADE = 3
    CLUB = 4

suit_lookup = {
    Card_Type.HEART: UNICODE_HEART,
    Card_Type.DIAMOND: UNICODE_DIAMOND,
    Card_Type.SPADE: UNICODE_SPADE,
    Card_Type.CLUB: UNICODE_CLUB   
}

class Test_Card:
    """For testing Card and deck validations"""
    def __init__(self, card_type, number, point_value):
        self.card_type = card_type
        self.card_number = number
        self.point_value = point_value

class Card:
    """Defines a poker card."""
    def __init__(self, card_type, number, point_value = 0):
        number_values = (2, 3, 4, 5, 6, 7, 8, 9, 'T', 'J', 'Q', 'K', 'A')

        if not isinstance(card_type, Card_Type):
            raise ValueError("Invalid card type. Must be a valid Card_Type enum value.")

        if number not in number_values:
            raise ValueError("The number must be a valid card value: 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A")

        self.__card_type = card_type
        self.__card_number = number
        self.__point_value = point_value
        self.hide = False

    @property
    def card_type(self):
        """Returns the Card_Type: Heart, Diamond, Spade, Club for the card."""
        return self.__card_type

    @property
    def display_card_type(self):
        """Returns the Card_Type: Heart: ♥, Diamond: ♦, Spade: ♠, Club: ♣ for the card."""
        return suit_lookup[self.__card_type]
    
    @property
    def card_number(self):
        """Returns the number for the card."""
        return self.__card_number

    @property
    def point_value(self):
        """The point value of the card if applicable"""
        return int(self.__point_value)

    def __eq__(self, other):
        """Compares suit and number of this card and the other card to determine equality."""
        if isinstance(other, Card):
            return self.card_type == other.card_type and self.card_number == other.card_number
            
        return False
    
    def __add__(self, other):
        """Adds the point value to other."""
        if not isinstance(other, int):
            raise TypeError("Unsupported operand type for +")

        return self.point_value + other
        