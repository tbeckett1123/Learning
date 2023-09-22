# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 2: Card Game: Card Game Demo and tests.
from Deck import Deck
from Hand import Hand
from Card import Card
from Card import Card_Type
from Card import Test_Card

def deal(deck, hand, hide = False):
    """Deals a card from the deck to the hand"""
    try:
        card = deck.draw()        
        card[0].hide = hide
        hand.accept(card[0])
    except ValueError as e:
        print(f"Error: {e}")

def show_hand(hand, show_hidden = False):
    """Prints the cards in the hand to std out"""
    #print the top row of cards display
    for i in range(0, len(hand)):
        card = hand.show(i)        
        if card.hide == True and show_hidden == False:
            print("XX", end = "")
        elif i > 0:
            print(f" {card.display_card_type} ", end = "")
        else:
            print(f"{card.display_card_type} ", end = "")
    print("")
    
    #print the bottom row of cards display
    for i in range(0, len(hand)):
        card = hand.show(i)
        if card.hide == True and show_hidden == False:
             print("XX", end = "")
        elif i > 0:
            print(f"  {card.card_number}", end = "")             
        else:
            print(f" {card.card_number}", end = "")
    print("")
    
    

def main():
    dealer_hand = Hand(11)
    player_hand = Hand(11)

    deck = Deck()
    deck.shuffle()

    # deal the intial hands to the player and the dealer
    deal(deck, player_hand)
    deal(deck, dealer_hand, True)
    deal(deck, player_hand)
    deal(deck, dealer_hand)

    #begin player hit or stand routine
    choice = "h"
    while choice == "h" and player_hand.score < 22:
        show_hand(dealer_hand)
        print("--------------------------")
        show_hand(player_hand)
        choice = input("hit(h) or stand(s): ")

        if choice == "h":
            deal(deck, player_hand)   
    
    #begin dealer hit or stand routine        
    if player_hand.score < 22:        
        print("Dealer's play")
        show_hand(dealer_hand, True)
        print("--------------------------")
        show_hand(player_hand)
        while dealer_hand.score < 17: # keep hitting till dealer hand is between 17 and 21
            print("Dealer hits")
            deal(deck, dealer_hand)
            show_hand(dealer_hand, True)
            print("--------------------------")
            show_hand(player_hand)            

    print("Show Dealer and Player hands.")

    show_hand(dealer_hand, True)
    print("--------------------------")
    show_hand(player_hand)    
    
    # determine the winner!
    if dealer_hand.score > 21:
        print("Dealer busts! You win!")
    elif player_hand.score > 21:
        print("You busted! You lose! Better luck next time.")
    elif dealer_hand.score > player_hand.score:
        print("Dealer wins! Better luck next time.")
    elif player_hand.score > dealer_hand.score:
        print("You win!")
    else:
        print("It's a tie. Better luck next time.")

    #return the cards to the deck for demo purposes
    print("Demo hand.discard and deck.add_card.")
    print("Dealer's cards")
    while len(dealer_hand) > 0:
        card = dealer_hand.discard(0)
        print(f"{card.display_card_type} {card.card_number}")
        deck.add_card(card)
    print("Player's cards")
    while len(player_hand) > 0:
        card = player_hand.discard(0)
        print(f"{card.display_card_type} {card.card_number}")
        deck.add_card(card)
    
    # Now check deck controls
    card = deck.draw()

    try:
        print("testing for invalid card type added to deck.")
        deck.add_card(Test_Card("UNO", "Wild", 0))
    except ValueError as e:
        print(e)
    
    try:        
        print("testing for duplicate in the deck.")
        deck.add_card(Card(Card_Type(card[0].card_type.value % 4 + 1), 2))
    except ValueError as e:
        print(e)

    deck.add_card(card[0])

    try:
        print("checking for adding to a full deck.")
        deck.add_card(card[0])
    except ValueError as e:
        print(e)

    print("demo deck reset and 52 card pick up")
    deck.reset()
    for i in range(0, 52):
        card = deck.draw()
        print(f"suit: {card[0].display_card_type}, {card[0].card_number}, points: {card[0].point_value}")

    print("Now try to draw from an empty deck.")
    try:
        deck.draw()
    except ValueError as e:
        print(e)

    print("Now check invalid card number")
    try:
        Card(Card_Type.HEART, 20)
    except ValueError as e:
        print(e)
    
    print("Now check invalid card type")
    try:
        Card("Uno", 2)
    except ValueError as e:
        print(e)

    print("Now check hand limit")
    try:
        hand = Hand(5)
        for i in range(2, 8):
            hand.accept(Card(Card_Type.HEART, i, i))
    except ValueError as e:
        print(e)

main()