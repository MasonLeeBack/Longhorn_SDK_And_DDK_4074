namespace ScreenSaver    // Namespace must be the same as what you set in project file
	{
		using System;
		using System.Collections;
		using MSAvalon.Windows.Controls;
		using MSAvalon.Windows;
		using MSAvalon.Windows.Navigation;
		using MSAvalon.Windows.Shapes;
		using MSAvalon.Windows.Media;
		using MSAvalon.Windows.Media.Animation;

		public partial class MyPage
		{
			private Ellipse[] balls;
			private Ellipse[] shadows;
			private Random rng;
			private int numBalls;
			private int windowHeight, windowWidth;
			private Time bounceDuration; // This is the amount of time (ms) until the balls 'explode'.
			private Time xAnimDuration;  // This is the amount of time (ms) it takes to go from left to right.
			private Timeline timeline;
			private SolidColorBrush gray, lightPurple, periwinkle, lightBlue, purple, pink;
			private RadialGradientBrush radialRed, radialBlue, radialGreen, radialYellow, radialOrange;
			private SolidColorBrush solidRed, solidBlue, solidGreen, solidYellow, solidOrange;

			//  Constants
			private const int shadowDist = 100;
			private const int minBalls = 3;
			private const int maxBalls = 10;
			private const int chanceSameColor = 25;
			private const int smallestRadius = 24;
			private const double shadowOpacity = 0.065;
			private const int largestRadius = smallestRadius + 2 * maxBalls;

			//  note: the hard-coded numbers within the code were chosen for visual and optimization reasons.

			private void Start(object sender, System.EventArgs e)
			{
				//  Get size of window
				NavigationApplication NavApp = MSAvalon.Windows.Application.Current as NavigationApplication;
				NavigationWindow NavWin;

				NavWin = NavApp.Windows[0] as NavigationWindow;
				windowWidth = Convert.ToInt32(NavWin.Width.Value);
				windowHeight = Convert.ToInt32(NavWin.Height.Value);
				InitColors();
				rng = new Random();

				// Set time for balls to move across screen/explode
				xAnimDuration = new Time(4000);
				bounceDuration = new Time(25200);

				// Grab the resources from the XAML file.
				LengthAnimationCollection centerXAnim = rootCanvas.FindResource("myCenterXAnim") as LengthAnimationCollection;
				LengthAnimationCollection centerYAnim = rootCanvas.FindResource("myCenterYAnim") as LengthAnimationCollection;
				LengthAnimationCollection radiusAnim = rootCanvas.FindResource("myRadiusAnim") as LengthAnimationCollection;

				// Create a master timeline that drives the ball animations.
				timeline = new Timeline();
				timeline.Begin = new Time(1000);						//  Pause to allow window to load
				timeline.Duration = bounceDuration + new Time(3000);	//  Added pause after balls fall off screen
				timeline.Repeated += (new EventHandler(OnRepeated));
				timeline.RepeatDuration = Time.Indefinite;

				// Create a number of balls with animations.
				balls = new Ellipse[maxBalls];
				shadows = new Ellipse[maxBalls];
				numBalls = rng.Next(minBalls, maxBalls);
				for (int i = 0; i < balls.Length; i++)
				{
					balls[i] = CreateGlobe(i, false);
					shadows[i] = CreateGlobe(i, true);
																		//  For bursting/falling:
					int randomGrowth = rng.Next(8, 13);					//  Growth rate will be between +8 and +13
					int fallRate = rng.Next(150, 200);					//  Fall rate will between 150% and 200%

					SetGlobeAnimations(balls[i], i, randomGrowth, fallRate, centerXAnim.Copy(), centerYAnim.Copy(), radiusAnim.Copy(), false);
					SetGlobeAnimations(shadows[i], i, randomGrowth, fallRate, centerXAnim.Copy(), centerYAnim.Copy(), radiusAnim.Copy(), true);

					// Add the ball to the canvas and to our ball collection.
					if (i < numBalls)
					{
						rootCanvas.Children.Add(balls[i]);
						rootCanvas.Children.Add(shadows[i]);
					}
				}

				int randomColorMethod = rng.Next(0, 100);				// Used to choose how to generate random colors.
				int randomColorOffset = rng.Next(0, 4);					// Used to choose base color for sequenced colors.

				// Assign colors to the balls
				ColorGlobes(balls, randomColorOffset, randomColorMethod, false);
				ColorGlobes(shadows, randomColorOffset, randomColorMethod, true);
			}


			private Ellipse CreateGlobe(int sizeFactor, Boolean isShadow)
			{
				Ellipse g = new Ellipse();

				g.RadiusX = new Length(smallestRadius + sizeFactor * 2);
				g.RadiusY = new Length(smallestRadius + sizeFactor * 2);

				// Set the parent timeline to the master timeline, which controls the start/repeat of the animations.
				g.Timeline = timeline;

				// Start the balls at the bottom left of the screen, start shadows shadowDist below that.
				int shadowDelta = (isShadow ? shadowDist : 0);

				g.CenterX = new Length(smallestRadius + maxBalls * 2);
				g.CenterY = new Length(windowHeight - (smallestRadius + maxBalls * 2) + shadowDelta);
				return g;
			}


			private void SetGlobeAnimations(Ellipse g, int offset, int randomGrowth, int fallRate, LengthAnimationCollection centerXAnimCopy, LengthAnimationCollection centerYAnimCopy, LengthAnimationCollection radiusAnimCopy, Boolean isShadow)
			{
				// Set the animations so that they start staggered in time.
				SetDelayedStart(centerXAnimCopy, offset);
				SetDelayedStart(centerYAnimCopy, offset);
				foreach (LengthAnimation laR in radiusAnimCopy)
				{
					laR.Begin = new TimeSyncValue(bounceDuration + new Time(10 * offset));
					laR.By = new Length(laR.By.Value * randomGrowth / 10.0);  // Have each ball explode to a random size.
				}

				SetYAnimations(g, offset, centerYAnimCopy, centerXAnimCopy, fallRate, isShadow);

				// Bind the animations to the ball's center position.
				g.SetAnimations(Ellipse.CenterXProperty, centerXAnimCopy);
				g.SetAnimations(Ellipse.CenterYProperty, centerYAnimCopy);
				g.SetAnimations(Ellipse.RadiusXProperty, radiusAnimCopy);
				g.SetAnimations(Ellipse.RadiusYProperty, radiusAnimCopy);
			}


			private void SetYAnimations(Ellipse g, int offset, LengthAnimationCollection centerYAnimCopy, LengthAnimationCollection centerXAnimCopy, int fallRate, Boolean isShadow)
			{
				LengthAnimation anim = centerXAnimCopy[0] as LengthAnimation;

				anim.By = new Length(windowWidth - 2 * largestRadius);
				anim.Duration = xAnimDuration;

				// The following 3 animations simulate a bouncing motion.
				anim = centerYAnimCopy[0] as LengthAnimation;
				anim.By = new Length((isShadow ? 1 : -1) * windowHeight - largestRadius);
				anim = centerYAnimCopy[1] as LengthAnimation;
				anim.To = g.CenterY;
				anim = centerYAnimCopy[2] as LengthAnimation;
				anim.To = g.CenterY;

				// Animation that causes general motion in the Y direction.
				anim = centerYAnimCopy[3] as LengthAnimation;
				anim.By = new Length(-windowHeight * 2 / 3);

				Double lastValue = anim.By.Value;

				// Animation that perturbs motion a bit in Y direction to keep it from being regular.
				anim = centerYAnimCopy[4] as LengthAnimation;
				anim.By = new Length(lastValue / 10.0);

				// Animation that makes the balls fall off the screen at different rates. Later balls fall at a later time that earlier balls.
				anim = centerYAnimCopy[5] as LengthAnimation;
				anim.Begin = new TimeSyncValue(bounceDuration + new Time(1000 + offset * 100));
				anim.By = new Length(windowHeight * fallRate / 100.0);
				anim.RepeatCount = 1;
			}


			private void SetDelayedStart(LengthAnimationCollection centerAnimCopy, int offset)
			{
				foreach (LengthAnimation la in centerAnimCopy)
				{
					int delta = 75 * offset;

					la.Begin = new TimeSyncValue(delta);
					la.RepeatDuration = bounceDuration - new Time(delta);
				}
			}


			private void OnRepeated(object sender, System.EventArgs e)
			{
				int randomColorMethod = rng.Next(0, 100); // Used to choose how to generate random colors.
				int randomColorOffset = rng.Next(0, 4);   // Used to choose base color for sequenced colors.

				//  Change number and color of balls randomly
				AdjustNumBalls();
				ColorGlobes(balls, randomColorOffset, randomColorMethod, false);
				ColorGlobes(shadows, randomColorOffset, randomColorMethod, true);
			}


			private void AdjustNumBalls()
			{
				rootCanvas.Children.Clear();
				numBalls = rng.Next(minBalls, maxBalls);
				for (int i = 0; i < balls.Length; i++)
				{
					if (i < numBalls)
					{
						rootCanvas.Children.Add(balls[i]);
						rootCanvas.Children.Add(shadows[i]);
					}
				}
			}


			private void ColorGlobes(Ellipse[] globes, int randomColorOffset, int randomColorMethod, Boolean isShadow)
			{
				// All the same color, with chanceSameColor% chance.
				if (randomColorMethod < chanceSameColor)
				{
					for (int i = 0; i < globes.Length; i++)
					{
						globes[i].Fill = (isShadow ? MakeSolidColoredBrush(randomColorOffset) : MakeColoredBrush(randomColorOffset));
					}

					rootCanvas.Background = CompBackgroundColor(randomColorOffset);
				}
				else
				{
					for (int i = 0; i < globes.Length; i++)
					{
						// Different colors starting at a random color.
						globes[i].Fill = (isShadow ? MakeSolidColoredBrush(i + randomColorOffset) : MakeColoredBrush(i + randomColorOffset));
					}

					rootCanvas.Background = RandomBackgroundColor();
				}
			}


			private Brush MakeColoredBrush(int i)
			{
				switch (i % 5)
				{
					case 0 :
						return radialRed;

					case 1 :
						return radialBlue;

					case 2 :
						return radialGreen;

					case 3 :
						return radialYellow;

					case 4 :
						return radialOrange;

					default :
						throw new Exception("Invalid Color Index");
				}
			}


			private Brush MakeSolidColoredBrush(int i)
			{
				switch (i % 5)
				{
					case 0 :
						return solidRed;

					case 1 :
						return solidBlue;

					case 2 :
						return solidGreen;

					case 3 :
						return solidYellow;

					case 4 :
						return solidOrange;

					default :
						throw new Exception("Invalid Color Index");
				}
			}


			private SolidColorBrush RandomBackgroundColor()
			{
				int chance = rng.Next(0, 5);

				return BackgroundColor(chance);
			}


			private SolidColorBrush BackgroundColor(int i)
			{
				switch (i)
				{
					case 0 :
						return gray;

					case 1 :
						return lightPurple;

					case 2 :
						return periwinkle;

					case 3 :
						return lightBlue;

					case 4 :
						return purple;

					case 5 :
						return gray;

					case 6 :
						return pink;

					default :
						throw new Exception("Invalid Color Index");
				}
			}


			private SolidColorBrush CompBackgroundColor(int colorOffset)
			{
				int chance = 0;

				//  Picks randomly from complementary background colors
				switch (colorOffset)
				{
					case 0 :
						chance = rng.Next(5, 6);
						break;

					case 1 :
						chance = rng.Next(0, 2);
						break;

					case 2 :
					case 3 :
						chance = rng.Next(3, 5);
						break;

					case 4 :
						chance = rng.Next(4, 5);
						break;
				}
				return BackgroundColor(chance);
			}


			private void InitColors()
			{
				//  background colors
				gray = new SolidColorBrush(Color.FromRGB(60, 60, 60));
				pink = new SolidColorBrush(Color.FromRGB(219, 89, 170));
				periwinkle = new SolidColorBrush(Color.FromRGB(109, 176, 199));
				lightBlue = new SolidColorBrush(Color.FromRGB(14, 154, 207));
				lightPurple = new SolidColorBrush(Color.FromRGB(164, 164, 210));
				purple = new SolidColorBrush(Color.FromRGB(122, 77, 164));

				// ball radial colors
				radialRed = new RadialGradientBrush(Color.FromRGB(255, 63, 63), Color.FromRGB(155, 43, 33));
				radialBlue = new RadialGradientBrush(Color.FromRGB(53, 53, 255), Color.FromRGB(33, 33, 155));
				radialGreen = new RadialGradientBrush(Color.FromRGB(53, 255, 53), Color.FromRGB(33, 155, 33));
				radialYellow = new RadialGradientBrush(Color.FromRGB(255, 255, 53), Color.FromRGB(220, 220, 10));
				radialOrange = new RadialGradientBrush(Color.FromRGB(255, 160, 53), Color.FromRGB(240, 70, 23));

				//  shadow solid colors
				solidRed = new SolidColorBrush(Color.FromRGB(255, 63, 63));
				solidBlue = new SolidColorBrush(Color.FromRGB(53, 53, 255));
				solidGreen = new SolidColorBrush(Color.FromRGB(53, 255, 53));
				solidYellow = new SolidColorBrush(Color.FromRGB(255, 255, 53));
				solidOrange = new SolidColorBrush(Color.FromRGB(255, 160, 53));

				solidRed.Opacity = shadowOpacity;
				solidBlue.Opacity = shadowOpacity;
				solidGreen.Opacity = shadowOpacity;
				solidYellow.Opacity = shadowOpacity;
				solidOrange.Opacity = shadowOpacity;
			}
		}
	}
