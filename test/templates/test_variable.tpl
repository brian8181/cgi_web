!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>{$page_title}</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link rel="shortcut icon" href="./favicon.png" />
	<link rel="stylesheet" type="text/css" href="./css/blue.css" />
	<script src="./script/functions.js" type="text/javascript"></script>
{* extra headers *}
{if isset($headers)}
{$headers}
{/if}
</head>
<body>
<div class="text_area">
<div class="box" style="text-align: center">
<h1>{$page_title}</h1>
{*TESTING*}
{*TESTING*}
{*TESTING*}
</div>


div class="titlepage"><div><div><h3 class="title">
<a name="boost_regex.syntax.leftmost_longest_rule"></a><a class="link" href="leftmost_longest_rule.html" title="The Leftmost Longest Rule">The Leftmost
      Longest Rule</a>
</h3></div></div></div>
<p>
        Often there is more than one way of matching a regular expression at a particular
        location, for POSIX basic and extended regular expressions, the "best"
        match is determined as follows:
      </p>
<div class="orderedlist"><ol class="orderedlist" type="1">
<li class="listitem">
            Find the leftmost match, if there is only one match possible at this
            location then return it.
          </li>
<li class="listitem">
            Find the longest of the possible matches, along with any ties. If there
            is only one such possible match then return it.
          </li>
<li class="listitem">
            If there are no marked sub-expressions, then all the remaining alternatives
            are indistinguishable; return the first of these found.
          </li>
<li class="listitem">
            Find the match which has matched the first sub-expression in the leftmost
            position, along with any ties. If there is only on such match possible
            then return it.
          </li>
<li class="listitem">
            Find the match which has the longest match for the first sub-expression,
            along with any ties. If there is only one such match then return it.
          </li>
<li class="listitem">
            Repeat steps 4 and 5 for each additional marked sub-expression.
          </li>
<li class="listitem">
            If there is still more than one possible match remaining, then they are
            indistinguishable; return the first one found.
          </li>
</ol></div>
</div>

<br />
<div style="text-align: center">
<a class="NoColor" href="http://validator.w3.org/check?uri=referer">
	<img src="./image/valid-xhtml10-blue.png" alt="Valid XHTML 1.0 Transitional" height="31" width="88" align="middle" />
</a>
</div>

<br />
{* contact info *}
<div style="text-align: center">
	{#mail_message#}
	<br />
	<a href="mailto:{#admin_email#}?subject=Web Password">{#admin_email#}</a>
</div>
<br />
<span style="font-size: smaller;"><em>Version {#version#} {#version_date#} ~(Copyright &#169; 2008)</em></span>
</div>
</body>
</html>