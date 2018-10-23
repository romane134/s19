function	showHideMenu()
{
	let elem = document.getElementById("menu").style;
	if (elem.right == "-180px")
	{
		elem.right = "0px";
	}
	else if (elem.right == "0px")
	{
		elem.right = "-180px";
	}
}

function	showHideMenu175()
{
	let elem = document.getElementById("menu").style;
	if (elem.right == "-175px")
	{
		elem.right = "0px";
	}
	else if (elem.right == "0px")
	{
		elem.right = "-175px";
	}
}

function	updateHTML()
{
	let input = document.getElementById("inHTML").value;
	document.getElementById("HTMLOutput").innerHTML = input;
}

function	updateHTMLWithCSS()
{
	let css = document.getElementById("UserCSS").value;
	let HTML = document.getElementById("UserHTML").value;
	document.getElementById("CSSInput").innerHTML = css;
	document.getElementById("UserResult").innerHTML = HTML;
}

function	felicitation(s)
{
	alert(s);
}