{* COMMENT TEST *}
{if $logged_in}
XYZ
{/if}
{config_load file="music.conf"}{include file="header_test.tpl"}
<br />
{if $logged_in}
Hello Its ME!
{/if}
{include file="body.tpl"}
<br />
{include file="footer_test.tpl"} 