Considerations

The main program file will be called CardGame.py  Card Game will do a basic black jack
The dealer AI will hit if the value of the dealer and is less than 17
For the sake of this demo of the card hand and deck class will not allow splitting or doubling down.
The rules of blackjack say that Ace can be 1 or 11 depending on the hand score.  To simply the game, I'm going to always make Ace 1

The card, hand, and deck class were created in project 2.

Following the insturctions for project 3 and the notes from project 2, I made the following changes:
I implemented __len__ on hand and deck.
I implemented __add__ and __radd__ on card.
I found that the the code from radd needed to be the same as add, and I found that I could remove add and only implement radd and sum works fine.
I used "\u2665" as opposed to char(0x2665) ...

I refactored the game a little.  I added a black jack auto win rule for the requirment for project 3, and I put some printing that was being repeated into a function.