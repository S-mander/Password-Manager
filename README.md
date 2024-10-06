-Password Manager

-This project is a C++ application for managing user passwords securely.
It validates passwords based on a set of criteria, encrypts them for storage, and verifies
passwords during authentication attempts. It additionally prevents the use of old passwords.

-Features:    
  Password Validation:
  Minimum 8 characters.
  Must include at least one uppercase letter, one lowercase letter, one digit, and one special character.
  Prevents spaces in the password.
  Ensures no reuse of previous passwords.
  
  Password Encryption:
  Encrypts the password using an offset-based approach.
  Uppercase, lowercase, and digits are encrypted with unique offsets.
  Offset values are included as part of the encrypted password for security.
  
  Password Management:
  Users can create and change their passwords.
  Old passwords are stored to avoid reuse.
  Password verification compares the encrypted input with the stored password.
