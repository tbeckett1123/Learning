Considerations

The main program file will be called CardGame.py  Card Game will do a basic black jack
The dealer AI will hit if the value of the dealer and is less than 17
For the sake of this demo of the card hand and deck class will not allow splitting or doubling down.
The rules of blackjack say that Ace can be 1 or 11 depending on the hand score.  To simply the game, I'm going to always make Ace 1

The card class needs to have
    property for club, heart, spade, and diamond
    property for the number of the card 2 - 10 and A, J, Q, K for formatting purposes 10 will be displayed as T
    property for the point value of the card.
The card class needs to protect the values from being changed after init to prevent players from cheating. Use  _ _ variables and getter properties
The card class needs to implement the __eq__ for "in" and comparision
The card class __init__ needs to accept card type, card number and optional point value
The card class __init__ needs to verify card type, and card number are valid values.

The hand class needs to have
    property for max size -- hand size
    property for size -- size of hand cards in hand array
    method accept a card in the deck
    method to fetch each card
    medthod to discard
    property for the hand score
    
The deck class
    There should be a size property that shows the number of cards in the deck.
    There should be a shuffle method. the shuffle method should shuffle the cards in the deck regardless whether it's in its initial state.
    There should be a draw method that will remove 1 card from the top of the deck.
    There should be a add_card method  will add a card to the deck as specified or to the bottom of the deck if not specified.
    There should be a reset deck that will return the deck back to it's initial state.
        The inital state will deep copy a list of the 52 cards in the deck.
    The __intit__ should create 52 poker card standard deck.
    
The card game
    The should be 2 hands dealer hand and player hand
    Each hand should accept up to 11 cards that is the upper case of cards: A A A A 2 2 2 2 3 3 3
    Players cards will be shown.
    Dealers 1st card will be hidden, and all all cards will be shown.
    1. The dealer routine will deal 2 cards to each player. player then dealer repeat 1.        
    2. then player gets to hit until stands or busts.
    3. then dealer get to hit until stands or busts.
        The dealer will hit if dealer's hand is less than 17
        
Randomization proved to be challenging.  While it does randomize the deck, it tends to favor dealing lower value cards more frequently.
I went through a few different tries.  the one in shuffle seems to have, base on game play observations, to have the best results.

I figured out the shuffling issue.  I  was thinking about it as randomizing.  When you shuffle a deck of cards you tend to do it more than once, so
I put my randomizing routine in a loop. QED.