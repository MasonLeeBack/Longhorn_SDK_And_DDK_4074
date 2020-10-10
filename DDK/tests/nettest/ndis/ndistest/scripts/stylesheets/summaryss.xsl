<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl" language="JScript">
<xsl:template match="/">
<HTML>
	<head>
		<style>
			BODY {  background-color: white; color: black;  font: 10pt; }
		</style>
	</head>
<BODY>
	
	<table border="0" width="100%" cellspacing="0" cellpadding="0">
	<tr>
		<td align="left" style="font-size: 7pt">
			<xsl:value-of select="NDTLogSummary/Date"/>
		</td>
	</tr>
	</table>
		
		<p align="center"><b>WHQL Summary</b></p>
		
		<hr width="100%" align="center" size="1"/>
		
		<table border="0" width="100%" cellspacing="0" cellpadding="0">
			<tr bgcolor="#C0C0C0">
				<td align="left" width="20%" style="font-size: 10pt; font-weight: bold">LogName</td>
				<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Total</td>
				<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Passed</td>
				<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Failed</td>
				<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Warned</td>
				<td align="center" width="15%" style="font-size: 10pt; font-weight: bold">Created</td>
				<td align="center" width="15%" style="font-size: 10pt; font-weight: bold">Duration</td>
			</tr>
			
			<xsl:for-each select="NDTLogSummary/NDTLog">
			<tr>
				<td align="left" width="20%" style="font-size: 10pt">
					<a><xsl:attribute name="href">#<xsl:value-of select="LogName"/></xsl:attribute><xsl:value-of select="LogName"/></a>
				</td>				 
				<td align="center" width="10%" style="font-size: 10pt">
					<xsl:value-of select="Summary//Total"/>
				</td>
				<td align="center" width="10%" style="font-size: 10pt">
					<xsl:value-of select="Summary//Passed"/>
				</td>
				<td align="center" width="10%" style="font-size: 10pt">
					<xsl:value-of select="Summary/Failed"/>
				</td>
				<td align="center" width="10%" style="font-size: 10pt">
					<xsl:value-of select="Summary//Warned"/>
				</td>
				<td align="center" width="15%" style="font-size: 10pt">
					<xsl:value-of select="Summary//Created"/>
				</td>
				<td align="center" width="15%" style="font-size: 10pt">
					<xsl:value-of select="Summary//Duration"/>
				</td>
			</tr>
			</xsl:for-each>
		</table>
		
		<br/>
		
		<table border="0" width="100%" cellspacing="0" cellpadding="">
		<tr bgcolor="#DCDCDC" >
			<td align="left" width="20%" style="font-size: 10pt">
				<b>Totals:</b>
			</td>
			<td align="center" width="10%" style="font-size: 10pt">
				<xsl:value-of select="NDTLogSummary/Summary/Total"/>
			</td>
			<td align="center" width="10%" style="font-size: 10pt">
				<xsl:value-of select="NDTLogSummary/Summary/Passed"/>
			</td>
			<td align="center" width="10%" style="font-size: 10pt">
				<xsl:value-of select="NDTLogSummary/Summary/Failed"/>
			</td>
			<td align="center" width="10%" style="font-size: 10pt">
				<xsl:value-of select="NDTLogSummary/Summary/Warned"/>
			</td>	
			<td align="center" width="15%" style="font-size: 10pt">
			</td>
			<td align="center" width="15%" style="font-size: 10pt">
			</td>
		</tr>
		</table>
		
		<br/>
		<hr width="100%" align="center" size="1"/>
		<br/>
		<br/>
		
		<pre>
		
		<xsl:for-each select="NDTLogSummary/NDTLog">
		
			<a><xsl:attribute name="name"><xsl:value-of select="LogName"/></xsl:attribute></a>
	
			<xsl:apply-templates select="Summary"/>		
			<xsl:apply-templates select="FailSummary"/>
			<xsl:apply-templates select="WarnSummary"/>
				
			<xsl:for-each select="*">
				<xsl:if language="JScript" expr="this.nodeName == 'Variation'"> 
					<xsl:apply-templates select="."/>
				</xsl:if>	
				<xsl:if language="JScript" expr="this.nodeName == 'Write'"> 
					<xsl:value-of select="."/><br/>
				</xsl:if>	
			</xsl:for-each>
		
		</xsl:for-each>
		
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
			<font color="red">FAILED:<xsl:value-of select="."/></font>
		</xsl:if>	
		<xsl:if language="JScript" expr="this.nodeName == 'Warned'"> 
			<font color="#CCCC00">WARNED:<xsl:value-of select="."/></font>
		</xsl:if>	
	</xsl:for-each>
	<br/>
</xsl:template>

<xsl:template match="Command">
<a><xsl:attribute name="href"><xsl:value-of select="Link"/></xsl:attribute><xsl:value-of select="Name"/></a>
</xsl:template>

<xsl:template match="Summary">
	<hr width="100%" align="center" size="1"/>
			
	<table border="0" width="100%" cellspacing="0" cellpadding="0">
		<tr bgcolor="#C0C0C0">
			<td align="left" width="20%" style="font-size: 10pt; font-weight: bold">LogName</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Total</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Passed</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Failed</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Warned</td>
			<td align="center" width="10%" style="font-size: 10pt; font-weight: bold">Duration</td>
		</tr>
		
		<tr>
			<td align="left" width="20%" style="font-size: 10pt"><xsl:value-of select="LogName"/></td>
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
