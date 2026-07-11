## Proof for triac calculation

We need to find a way to lineralise the relation between $p \in [0;1]$ and the energy delivered ($\int_{\theta}^{\pi}sin^2(x)\,dx$)
we need to find a relation between p and $\theta$ that acomplish it

$$\begin{array}{rcl}
 \int_{\theta}^{\pi}sin^2(x)\,dx & = & \int_{\theta}^{\pi}\frac{1-cos(2x)}{2}\,dx \\
 & = & \int_{\theta}^{\pi}\frac{1}{2}\,dx-\int_{\theta}^{\pi}\frac{cos(2x)}{2}\,dx \\
 & = & \frac{1}{2}\bigg( \int_{\theta}^{\pi}1\,dx-\int_{\theta}^{\pi}cos(2x)\,dx \bigg) \\
& = & \frac{1}{2}\bigg( \int_{\theta}^{\pi}1\,dx-\int_{\theta}^{\pi}cos(2x)\,dx \bigg) \\
& = & \frac{1}{2}\bigg( \left[ x\right]_{\theta}^{\pi}-\left[ \frac{sin(2x)}{2} \right]_{\theta}^{\pi}\bigg) \\
& = & \frac{1}{2} \bigg( \pi -\theta - \frac{sin(2\pi) - sin(2\theta)}{2} \bigg) \\
& = & \frac{\pi}{2} - \frac{\theta}{2} + \frac{sin(2\theta)}{4}
\end{array}$$


$$
\begin{array}{rcl}
&p\bigg( \frac{\pi}{2} - \frac{0}{2} + \frac{sin(0)}{4} \bigg)  =\frac{\pi}{2} - \frac{\theta}{2} + \frac{sin(2\theta)}{4} \\
\Leftrightarrow &  {p\pi}  =\pi - \theta + \frac{sin(2\theta)}{2} \\
\Leftrightarrow &  {p}  =  1 - \frac{\theta}{\pi} + \frac{sin(2\theta)}{2\pi} \\
\end{array}$$
