package it.finsoft.RoomReserve.validator;

import it.finsoft.RoomReserve.model.User;
import it.finsoft.RoomReserve.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.validation.Errors;
import org.springframework.validation.ValidationUtils;
import org.springframework.validation.Validator;

@Component
public class UserValidator implements Validator 
{
    @Autowired
    private UserService userService;

    @Override
    public boolean supports(Class<?> aClass)
    {
        return User.class.equals(aClass);
    }

    @Override
    public void validate(Object o, Errors errors)
    {
        User user = (User) o;
        //USERNAME
        ValidationUtils.rejectIfEmptyOrWhitespace(errors, "username", "NotEmpty");
        if (user.getUsername().length() < 1 || user.getUsername().length() > 10)
        {
            errors.rejectValue("username", "Size.userForm.username");
        }
        if (userService.findByUsername(user.getUsername()) != null)
        {
            errors.rejectValue("username", "Duplicate.userForm.username");
        }
        
        //NAME
        ValidationUtils.rejectIfEmptyOrWhitespace(errors, "name", "NotEmpty");//this line is for checking emptyness
        if (user.getName().length() <1  || user.getName().length() > 10)//this line is for checking size
        {
            errors.rejectValue("name", "Size.userForm.name");
        }
       
     
        //EMAIL
        ValidationUtils.rejectIfEmptyOrWhitespace(errors, "email", "NotEmpty");
        if (userService.findByEmail(user.getEmail()) != null)
          {  errors.rejectValue("email", "Duplicate.userForm.email"); }
        
        //PASSWORD
        ValidationUtils.rejectIfEmptyOrWhitespace(errors, "password", "NotEmpty");
        if (user.getPassword().length() < 1 || user.getPassword().length() > 10)
        {
            errors.rejectValue("password", "Size.userForm.password");
        }
        
        //PASSWORDCONFIRM
        if (!user.getPasswordConfirm().equals(user.getPassword())) {
            errors.rejectValue("passwordConfirm", "Diff.userForm.passwordConfirm");
        }
    }
}