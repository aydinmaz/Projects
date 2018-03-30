package it.finsoft.RoomReserve.repository;

import org.springframework.data.repository.CrudRepository;

import it.finsoft.RoomReserve.model.User;

public interface UserRepository extends CrudRepository<User, Long> {
    User findByUsername(String username);
    User findByEmail(String email);
}
