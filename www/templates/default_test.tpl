{config_load file="music.conf"}{include file="header_test.tpl"}
<br />
{if $logged_in}
Welcome,<font color="{#fontColor#}">{$name}!</font>
{else}
hi, {$name}
{/if}
{include file="body.tpl"}
<br />
{include file="footer_test.tpl"}