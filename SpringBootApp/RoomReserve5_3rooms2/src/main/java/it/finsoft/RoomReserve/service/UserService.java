package it.finsoft.RoomReserve.service;

import it.finsoft.RoomReserve.model.User;

public interface UserService {

	 public void save(User user);
	 public User findByUsername(String username);
	 public User findByEmail(String email);
	
}
