#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>


class UserPasswordManager{
private:
	bool validPass;
	std::string currentPass;
	std::vector<std::string> oldPass;
	
	bool validatePassword(std::string& password) {
	    // Check length
	    if (password.length() < 8) {
	        return false;
	    }
	
	    // Check for lower case
	    bool hasLower = false;
	    for (char ch : password) {
	        if (std::islower(ch)) {
	            hasLower = true;
	            break;
	        }
	    }
	    if (!hasLower) {
	        return false;
	    }
	
	    //check for uppercase
	    bool hasUpper = false;
	    for (char ch : password) {
	        if (std::isupper(ch)) {
	            hasUpper = true;
	            break;
	        }
	    }
	    if (!hasUpper) {
	        return false;
	    }
	
	    //check for digit
	    bool hasDigit = false;
	    for (char ch : password) {
	        if (std::isdigit(ch)) {
	            hasDigit = true;
	            break;
	        }
	    }
	    if (!hasDigit) {
	        return false;
	    }
	
	    //check for special char
	    std::string specialChars = "!@#$%^&*()_+=-'<>?:\"/|[]{}";
	    bool hasSpecial = false;
	    for (char ch : password) {
	        if (specialChars.find(ch) != std::string::npos) {
	            hasSpecial = true;
	            break;
	        }
	    }
	    if (!hasSpecial) {
	        return false;
	    }
	    if (password.find(' ') != std::string::npos) {
        	return false;
    	}

		//check for old password
    	for (std::string& old : oldPass) {
        	if (password == old) {
            	return false;
        	}
    	}
	
	
	    return true;
}

    std::string encryptPassword(std::string& password) {
    // Encrypt uppercase letters
		std::string encryptedPassword = password;
		int uppercaseOffset = 0;
		int lowercaseOffset = 0;
		int digitOffset = 0;
		
		    // Encrypt uppercase letters and uppercase offset
		for (char& ch : encryptedPassword) {
		    if (std::isupper(ch)) {
		        int offset = (std::toupper(ch) - 'A' + 1) % 26;
		        ch = 'A' + offset;
		        uppercaseOffset += offset;
		    }
		}
		
		    // Encrypt lowercase letters and lowercase offset
		for (char& ch : encryptedPassword) {
		    if (std::islower(ch)) {
		        int offset = (std::tolower(ch) - 'a' + 1) % 26;
		        ch = 'a' + offset;
		        lowercaseOffset += offset;
		    }
		}
		
		    // Encrypt digits and digit offset
		for (char& ch : encryptedPassword) {
		    if (std::isdigit(ch)) {
		        int offset = (ch - '0') % 10;
		        ch = '0' + offset;
		        digitOffset += offset;
		    }
		}
		
		    // Increment value by individual offsets
		for (char& ch : encryptedPassword) {
		    if (std::isupper(ch)) {
		        ch += uppercaseOffset;
		    } else if (std::islower(ch)) {
		        ch += lowercaseOffset;
		    } else if (std::isdigit(ch)) {
		        ch += digitOffset;
		    }
		}
		
		std::string offsetDigits = std::to_string(uppercaseOffset) + std::to_string(lowercaseOffset)
                               + std::to_string(digitOffset);
    							 encryptedPassword = offsetDigits + encryptedPassword;
	
	    return encryptedPassword;
    }

    std::string createPassword() {
        std::string password;

        std::cout << "Enter a password: ";
        std::getline(std::cin, password);

        if (validatePassword(password)) {
            std::string encryptedPassword = encryptPassword(password);
            oldPass.push_back(encryptedPassword);
            return encryptedPassword;
        } else {
            return "";
        }
    }
	
public:
	UserPasswordManager() {
        validPass = false;
        currentPass = createPassword();
        if (!currentPass.empty()) {
            validPass = true;
            std::cout << "Password created" << std::endl;
        } else {
            std::cout << "Password could not be created" << std::endl;
        }
    }
    
    void changePassword() {
        std::string newPassword;
        std::cout << "Enter a new password: ";
        std::getline(std::cin, newPassword);

        if (validatePassword(newPassword)) {
            oldPass.push_back(currentPass);
            currentPass = encryptPassword(newPassword);
            std::cout << "Password was successfully changed" << std::endl;
        } else {
            std::cout << "Password was not changed" << std::endl;
        }
    }
    
    bool verifyPassword(std::string& password) {
        std::string encryptedPassword = encryptPassword(password);
        return (encryptedPassword == currentPass);
    }
	
	std::string getPassword() {
        return currentPass;
    }
    
 
	
};

int main(){
	UserPasswordManager passwordManager;


    passwordManager.getPassword();
   

    
    passwordManager.changePassword();

    
    std::string inputPassword;
    std::cout << "Enter a password to verify: ";
    std::getline(std::cin, inputPassword);
    
    if (passwordManager.verifyPassword(inputPassword)) {
        std::cout << "Password verification successful" << std::endl;
    } else {
        std::cout << "Password verification failed" << std::endl;
    }
	
	
	
	return 0;
}
