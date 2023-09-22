# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 3: Blackjack: Hand class
from Card import Card

class Hand:
    """Defines the hand size and rules associated with card being displayed."""
    def __init__(self, hand_size = 5):
        self.__max = hand_size
        self.__hand = []
    
    def __len__(self):
        """The current size of the hand."""
        return len(self.__hand)

    @property
    def max(self):
        """The max size of the hand."""
        return self.__max

    @property
    def score(self):
        """Tallies the score for the hand."""
        return sum(self.__hand)

    def show(self, card_number):

        if card_number >= len(self) or card_number < 0:
            raise ValueError("Invalid card number.")
        
        return self.__hand[card_number]

    def accept(self, card):
        """Takes the passed card and puts it in the hand."""
        if len(self) > self.max - 1:
            raise ValueError("The hand is full.")
        
        if not isinstance(card, Card):
            raise ValueError("Invalid card. Must be a valid Card value.")

        self.__hand.append(card)

    def discard(self, index):
        """discards the card to the specified index from the hand"""

        if not self.__hand:
            raise ValueError("The hand is empty.")

        size = len(self)

        if size == 1:
            return self.__hand.pop()
        
        if index >= size or index < 0:
            raise ValueError(f"Invalid index. the current size is {size}.")

        return self.__hand.pop(index)

    def sum(self):
        """Tallies the points for the cards in the hand."""
        total = 0

        for card in self.__hand:
            total = card + total

        return total