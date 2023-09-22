import tkinter as tk

class Modal:
    def __init__(self, parent, title, message, height, width):
        self.dialog = tk.Toplevel(parent)
        self.dialog.title(title)
        self.dialog.geometry(f"{width}x{height}")
        self.dialog.resizable(False, False)

        self.label = tk.Label(self.dialog, text = message, font = ("Arial", 10, "bold"))
        self.label.pack(pady=20)

        self.ok_button = tk.Button(self.dialog, text="OK", command=self.dialog.destroy)
        self.ok_button.pack(expand = True, fill = tk.BOTH, anchor = tk.S)

        # Make the dialog modal
        self.dialog.transient(parent)  # Set parent window
        self.dialog.wait_visibility()
        self.dialog.grab_set()  # Set focus to the dialog        
        parent.wait_window(self.dialog)  # Wait for the dialog to be closed before continuing        
