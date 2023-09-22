# Name: Timothy Beckett
# Class: CSCI 3038 - Python
# Project 3: Blackjack
# Black Jack Black playing Blackjack holding a black jack eating craker jacks
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

def show_table(dealer_hand, player_hand, show_hidden = False):
    show_hand(dealer_hand, show_hidden)
    print("--------------------------")
    show_hand(player_hand)       

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
    while choice == "h" and player_hand.score < 22 and player_hand.score != 21:
        show_table(dealer_hand, player_hand)
        choice = input("hit(h) or stand(s): ")

        if choice == "h":
            deal(deck, player_hand)   
    
    #begin dealer hit or stand routine        
    #player wins if 21 no point in playing it out
    #player loses if over 21 again no piont
    if player_hand.score < 21:        
        print("Dealer's play")
        show_table(dealer_hand, player_hand, True)
        while dealer_hand.score < 17: # keep hitting till dealer hand is between 17 and 21
            print("Dealer hits")
            deal(deck, dealer_hand)
            show_table(dealer_hand, player_hand, True)         

    print("Show Dealer and Player hands.")

    show_table(dealer_hand, player_hand, True)   

    # determine the winner!
    if player_hand.score == 21:
        print("Blackjack!!!! You win!")
    elif dealer_hand.score > 21:
        print("Dealer busts! You win!")
    elif player_hand.score > 21:
        print("You busted! You lose! Better luck next time.")
    elif dealer_hand.score > player_hand.score:
        print("Dealer wins! Better luck next time.")
    elif player_hand.score > dealer_hand.score:
        print("You win!")
    else:
        print("It's a tie. Better luck next time.")

main()