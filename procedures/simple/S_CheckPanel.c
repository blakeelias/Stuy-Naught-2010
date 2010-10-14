//Check if panel was found

if (isPanelFound())
{
 getPanelState(panelState);


//Do something to make this "in front of panel"
 panelState[4] = panelState[0];
 panelState[5] = panelState[1];
 panelState[6] = panelState[2];

 state = STATE_TOPANEL;
 break;
}

