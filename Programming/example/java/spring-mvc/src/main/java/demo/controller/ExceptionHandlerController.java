package demo.controller;

import java.io.IOException;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

/**
 */
@RestControllerAdvice
public class ExceptionHandlerController {
	@ExceptionHandler(IOException.class)
	public ResponseEntity<String> handle(IOException e) {
		return ResponseEntity.internalServerError()
				.body(e.getMessage());
	}
}
