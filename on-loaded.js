//alert(document.forms[0].action);
if (document.forms[0]) {
	if (document.forms[0].action =='https://192.168.42.190/prelogin') {
		if (document.forms[0] && document.forms[0].elements[0]) {
			document.forms[0].elements[0].value="Alex";
		}
		document.forms[0].submit();
	}
	if (document.forms[0].action =='https://192.168.42.190/j_security_check') {
		if (document.forms[0] && document.forms[0].elements[0]) {
			document.forms[0].elements[0].value="Alex";
		}
		if (document.forms[0] && document.forms[0].elements[1]) {
			document.forms[0].elements[1].value="alexSeins83";
		}
		//alert('Wait');
		window.setTimeout(
			function() {
				doLogin();
			},
			100
		);
	}
}
