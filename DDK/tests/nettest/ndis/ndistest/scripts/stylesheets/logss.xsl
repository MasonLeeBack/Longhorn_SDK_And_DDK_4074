<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl" version="1.0">

<xsl:template match="/">
<HTML>
<head>
	<SCRIPT LANGUAGE="VBScript">
	<xsl:comment>
	<![CDATA[
	'
	' Open  the script associated with this log file in write.exe
	'
	Function ViewScript(strScriptName)
	Dim oShell, oFso
	
		Set oFso = CreateObject("Scripting.FileSystemObject")
		If (oFso.FileExists(strScriptName) = vbFalse) Then
			MsgBox "Unable to find file " & strScriptName & ".", vbExclamation Or vbOkOnly, "File Not Found"
			Exit Function
		End If
		
		Set oShell = CreateObject("WScript.Shell")
		oShell.Run("Write " & strScriptName)
	
	Set oShell = Nothing
	End Function
	]]>
	</xsl:comment>
    </SCRIPT>	
<style>
	BODY {background-color:white; color:black; font:10pt;}
	.clsFailed {color:red;}
</style>
</head>
<BODY>	
	<XML>
	<Created><xsl:value-of select="/NDTLog/Summary/Created"/></Created>
	<Duration><xsl:value-of select="NDTLog/Summary/Duration"/></Duration>
	<Total><xsl:value-of select="NDTLog/Summary/Total"/></Total>
	<Passed><xsl:value-of select="NDTLog/Summary/Passed"/></Passed>
	<Failed><xsl:value-of select="NDTLog/Summary/Failed"/></Failed>
	<Warned><xsl:value-of select="NDTLog/Summary/Warned"/></Warned>
	<ScriptName><xsl:value-of select="/NDTLog/ScriptFullName"/></ScriptName>
	</XML>
<pre>	
	<table border="0" width="100%" cellspacing="0" cellpadding="0">
	<tr>
		<td align="center"><b><xsl:value-of select="NDTLog/LogTitle"/></b></td>
	</tr>
	</table>
	<xsl:apply-templates select="NDTLog/Summary"/>
	<xsl:apply-templates select="NDTLog/FailSummary"/>
	<xsl:apply-templates select="NDTLog/WarnSummary"/>
	<xsl:for-each select="NDTLog/*">
	
		<xsl:if language="JScript" expr="this.nodeName == 'Variation'"> 
			<xsl:apply-templates select="."/>
		</xsl:if>	
	
		<xsl:if language="JScript" expr="this.nodeName == 'Write'">
			<xsl:value-of select="."/>
		</xsl:if>
		
	</xsl:for-each>
	<br/>
	<br/>
	<div align="left">#################### END OF LOG ####################</div>
</pre>
</BODY>
</HTML>
</xsl:template>
<xsl:template match="Variation">
<a><xsl:attribute name="name"><xsl:value-of select="BookMark"/></xsl:attribute></a>
<font color="0000FF" ><b><u>Variation #<xsl:value-of select="Number"/>:</u></b></font><xsl:value-of select="Description"/>
	<xsl:for-each select="*">	
		<xsl:if language="JScript" expr="this.nodeName == 'Write'"> 
			<xsl:value-of select="."/>
		</xsl:if>	
		<xsl:if language="JScript" expr="this.nodeName == 'Command'"> 
			<xsl:apply-templates select="."/>
		</xsl:if>	
		<xsl:if language="JScript" expr="this.nodeName == 'Failed'"> 
			<font color="#FF0000">FAILED:<xsl:value-of select="."/></font>
		</xsl:if>	
		<xsl:if language="JScript" expr="this.nodeName == 'Warned'"> 
			<font color="#CCCC00">WARNED:<xsl:value-of select="."/></font>
		</xsl:if>	
	</xsl:for-each>
	<xsl:choose>
		<!-- <xsl:when test=".[@Result = 'Passed']"><font color="#008000">VARIATION PASSED</font><br/></xsl:when> -->
		<xsl:when test=".[@Result = 'Warned']"><font color="#CCCC00">VARIATION WARNED</font><br/></xsl:when>
		<xsl:when test=".[@Result = 'Failed']"><font color="#FF0000">VARIATION FAILED</font><br/></xsl:when>
	</xsl:choose>
</xsl:template>
<xsl:template match="Command">
<a><xsl:attribute name="href"><xsl:value-of select="Link"/></xsl:attribute><xsl:value-of select="Name"/></a>
</xsl:template>
<xsl:template match="Summary">
<hr width="100%" align="center" size="1"/>
			
	<table border="0" width="100%" cellspacing="0" cellpadding="0">
		<tr bgcolor="#C0C0C0">
			<td align="left" width="20%" style="font-size: 10pt; font-weight: bold">ScriptName</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Total</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Passed</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Failed</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Warned</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Duration</td>
		</tr>
		
		<tr>
			<td align="left" width="20%" style="font-size: 10pt">
				<a>
				<xsl:attribute name="href">vbscript:ViewScript("<xsl:value-of select="/NDTLog/ScriptFullName"/>")</xsl:attribute>
				<xsl:value-of select="/NDTLog/ScriptName"/>
				</a>
			</td>
			<td align="center" width="10%" style="font-size: 10pt"><xsl:value-of select="Total"/></td>
			<td align="center" width="10%" style="font-size: 10pt"><xsl:value-of select="Passed"/></td>
			<td align="center" width="10%" style="font-size: 10pt"><xsl:value-of select="Failed"/></td>
			<td align="center" width="10%" style="font-size: 10pt"><xsl:value-of select="Warned"/></td>
			<td align="center" width="10%" style="font-size: 10pt"><xsl:value-of select="Duration"/></td>
			</tr>
	</table>
			
	<br/>
	<hr width="100%" align="center" size="1"/>			
			
</xsl:template>

<xsl:template match="FailSummary">
	
	<u><b><font color="red" size="2">Failed Variations:</font></b></u><br/>
	
	<xsl:for-each select="Failure">
		<a><xsl:attribute name="href"><xsl:value-of select="Link"/></xsl:attribute>Variation <xsl:value-of select="VariationNumber"/>:</a><xsl:value-of select="Description"/>
	</xsl:for-each>
	
	<hr/>
</xsl:template>

<xsl:template match="WarnSummary">
	
	<u><b><font color="#CCCC00" size="2">Warned Variations:</font></b></u><br/>
	
	<xsl:for-each select="Warning">
		<a><xsl:attribute name="href"><xsl:value-of select="Link"/></xsl:attribute>Variation <xsl:value-of select="VariationNumber"/>:</a><xsl:value-of select="Description"/>
	</xsl:for-each>
	
	<hr/>
</xsl:template>

</xsl:stylesheet>
