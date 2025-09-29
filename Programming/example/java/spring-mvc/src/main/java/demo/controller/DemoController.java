package demo.controller;

import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.CookieValue;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestAttribute;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.SessionAttribute;

/**
 */
@Controller
@RequestMapping("/demo")
public class DemoController {

	@GetMapping(path = "/obj/{id}", consumes = { MediaType.APPLICATION_XML_VALUE }, produces = {
			MediaType.APPLICATION_JSON_VALUE })
	public String getObj(
			@PathVariable int id,
			@RequestBody int reqBody,
			@RequestHeader(HttpHeaders.ACCEPT) String accept,
			@RequestParam("param") String param,
			@SessionAttribute("sessionAttr") String sessionAttr,
			@RequestAttribute("reqAttr") String reqAttr,
			@ModelAttribute("modelAttr") String modelAttr,
			@CookieValue("JSESSIONID") String sessionId,
			Model model) {
		model.addAttribute("id", id);
		return "/views/index";
	}

	@ResponseBody
	@GetMapping("/api/obj/{filename:^[a-zA-Z0-9_-]+\\.txt$}")
	public Object getObj(@PathVariable String filename) {
		return new Object();
	}

	@GetMapping("/api/obj")
	public ResponseEntity<Object> getObj() {
		return ResponseEntity.ok()
				.contentType(MediaType.APPLICATION_JSON)
				.header(HttpHeaders.LOCATION, "inline;")
				.body(new Object());
	}

}
