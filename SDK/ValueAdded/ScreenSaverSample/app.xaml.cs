namespace ScreenSaver
{
	using System;
	using MSAvalon.Windows;
	using MSAvalon.Windows.Navigation;
	using MSAvalon.Windows.Input;

	public partial class MyApp
	{
		//  screenSaverPage string contains the xaml file name that should be shown
		//  Be sure to change screenSaverPage to your screen saver xaml page
		private const string screenSaverPage = "bounce.xaml";

		protected override void OnStartingUp (StartingUpCancelEventArgs e)
		{
			// Setup the application window.
			_window = new NavigationWindow ();
			_window.TopMost = true;
			_window.CanResize = false;
			_window.WindowStyle = WindowStyle.None;
			_window.WindowState = WindowState.Maximized;
			Mouse.OverrideCursor = Cursor.None;
			_isFirstMouseClick = true;

			//Navigate to your page
			_window.Navigate (new Uri (screenSaverPage, false, true));
			_window.Show ();
			_window.Focus ();
			base.OnStartingUp (e);

			//  Add keyboard and mouse event handlers
			_window.AddHandler (Keyboard.KeyDownEventID, new KeyEventHandler (DoSSKeyDown), true);
			_window.AddHandler (Mouse.MouseRightButtonDownEventID, new MouseButtonEventHandler (DoSSMouseRightButtonDown), true);
			_window.AddHandler (Mouse.MouseLeftButtonDownEventID, new MouseButtonEventHandler (DoSSMouseLeftButtonDown), true);
			_window.AddHandler (Mouse.MouseWheelEventID, new MouseWheelEventHandler (DoSSMouseWheel), true);
			_window.AddHandler (Mouse.MouseMoveEventID, new MouseEventHandler (DoSSMouseMove), true);
		}

		private void DoSSMouseWheel (object sender, MouseWheelEventArgs e)
		{
			Shutdown ();
		}

		private void DoSSMouseRightButtonDown (object sender, MouseButtonEventArgs e)
		{
			Shutdown ();
		}

		private void DoSSMouseLeftButtonDown (object sender, MouseButtonEventArgs e)
		{
			Shutdown ();
		}

		private void DoSSMouseMove (Object sender, MouseEventArgs s)
		{
			//ignores first mouse move triggered by window appearing under mouse
			if (_isFirstMouseClick)
			{
				_isFirstMouseClick = false;

				//  determines mouse position relative to window
				_initMouseLoc = Mouse.PrimaryDevice.GetPosition (_window);
			}
			else
			{
				Point currentMouseLoc = Mouse.PrimaryDevice.GetPosition (_window);

				//  Shuts down application only if physical location of mouse has changed,
				//  ignoring programmatic mouse moves.
				if (!currentMouseLoc.Equals (_initMouseLoc))
					Shutdown ();
			}
		}

		private void DoSSKeyDown (Object sender, KeyEventArgs s)
		{
			Shutdown ();
		}

		private Boolean _isFirstMouseClick;
		private Point _initMouseLoc;
		NavigationWindow _window;
	}
}
