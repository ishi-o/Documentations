package demo.controller;

import org.springframework.http.MediaType;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 */
@RestController
@RequestMapping("/demo")
public class DemoController {
	@GetMapping(path = "/obj", produces = { MediaType.APPLICATION_JSON_VALUE })
	public String getObj(@RequestParam("param") String param, Model model) {
		return "/views/index";
	}

}
