package it.finsoft.RoomReserve.repository;



import java.util.List;

//import java.util.List;

import org.springframework.data.repository.CrudRepository;

import it.finsoft.RoomReserve.model.Room;

public interface RoomRepository extends CrudRepository<Room, Long> {
	
	public List<Room> findAll();//mesl inke in yek function hast 
	
	
}

