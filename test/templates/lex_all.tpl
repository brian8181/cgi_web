AA
{if}
{HTML
    ABC 
}
{include}
EDF
{else}
XYZ
{config_load = file}
AAAA
{test}
CCCC
{foreach from}
{/foreach}
{$test}
{$two|default}
{default}

