# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 3: Blackjack: Deck class
from Card import Card
from Card import Card_Type
import random
import copy

class Deck:
    """A 52 card poker deck."""
    def __init__(self):
        self.__base_deck = []
        self.__deck = []

        for suit in range(1, 5, 1):
            for value in range(1, 14, 1):
                card_value = value
                point_value = value
                
                # setting face card values.
                if value == 1:
                    card_value = "A"
                elif value == 10:
                    card_value = "T"
                elif value == 11:
                    card_value = "J"
                    point_value = 10
                elif value == 12:
                    card_value = "Q"
                    point_value = 10
                elif value == 13:
                    card_value = "K"
                    point_value = 10                
                
                self.__base_deck.append(Card(Card_Type(suit), card_value, point_value)) # base deck is used for reseting the deck verifying a valid card.
                self.__deck.append(Card(Card_Type(suit), card_value, point_value))

    def __len__(self):
        """The current size of the deck"""
        return len(self.__deck)


    def shuffle(self):
        """shuffles the deck"""
        # randomize the cards will destroy the temp deck as the cards are added to deck
        for i in range(0, 10):   
            random.shuffle(self.__deck)

    def draw(self, number_of_cards = 1):
        """Deals the specified number of cards.  The default is 1 card."""

        size = len(self)

        if size == 0:
            raise ValueError("The deck is empty.")

        if number_of_cards > size:
            number_of_cards = size
        
        cards = [] # returning a list even if it's 1 card to make the data returned easier to process

        for card_count in range(0, number_of_cards, 1):
            cards.append(self.__deck.pop(0)) # the zero is to deal cards from the top of the deck.

        return cards

    def reset(self):
        """Returns the deck of cards back to its inital state."""
        self.__deck = copy.deepcopy(self.__base_deck)

    def add_card(self, card, position = 51):
        """Adds a card to the deck.  By default it will be added to the bottom of the deck."""

        size = len(self)

        if size > 51:
            raise ValueError("The deck is full.")

        if not isinstance(card.card_type, Card_Type):
            raise ValueError("Invalid card. Must be a valid poker card.")
        
        if card not in self.__base_deck:
            raise ValueError("The card is not a valid poker card.")

        if card in self.__deck:
            raise ValueError("The card is already in the deck.")

        if position < 0 or position > size - 1:
            self.__deck.append(card)
        else:
            self.__deck.insert(position, card)