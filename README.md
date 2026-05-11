<h1 align="center">Ray Tracing Engine</h1>

<p align="center">
  <em>An offline path tracer built from scratch in C++ — no graphics APIs, just vectors and recursive ray bounces.</em>
</p>

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/C%2B%2B-no_third_party_libs-7aa2f7?style=flat-square&labelColor=11141b">
  <img alt="Reference" src="https://img.shields.io/badge/Following-Ray_Tracing_in_One_Weekend-f7768e?style=flat-square&labelColor=11141b">
</p>

<p align="center">
  <a href="https://viniciusdugue.dev/projects/ray-tracing/index.html">
    <img src="https://viniciusdugue.dev/projects/ray-tracing/img/final-scene.png" alt="Final ray-traced scene with diffuse, metal, and dielectric spheres" width="720">
  </a>
</p>

<p align="center">
  <a href="https://viniciusdugue.dev/projects/ray-tracing/index.html"><b>→ Project page on viniciusdugue.dev</b></a>
</p>

---

## About

This is a from-scratch implementation of a **recursive path tracer**, built while working through Peter Shirley's *Ray Tracing in One Weekend*. No OpenGL, no Vulkan, no precompiled libraries — every pixel is the result of a ray cast into the scene, bounced off surfaces according to material BRDFs, and accumulated over hundreds of samples.

The point wasn't to be fast. The point was to understand *what a graphics API is actually doing under the hood* — how rays are generated, how intersections are computed, how light scatters off different materials, why noise looks the way it does. By the end, the engine renders the classic cover-image scene from the book: a sea of randomly placed spheres with glass, diffuse, and metal materials.

## What it implements

- **Ray generation.** Pinhole camera with configurable position, target, up-vector, and vertical FOV.
- **Sphere intersection.** Closed-form quadratic solve for ray–sphere hits, sorted by distance.
- **Antialiasing.** Multiple jittered rays per pixel, averaged for clean edges.
- **Lambertian diffuse.** Random unit-sphere scattering — matte, color-tinted surfaces.
- **Metal.** Mirror reflection with optional fuzz factor for imperfect surfaces.
- **Dielectric.** Refraction via Snell's law + Schlick approximation for Fresnel — convincing glass.
- **Defocus blur.** Lens-aperture sampling for depth-of-field effects.
- **Gamma correction.** sRGB output mapping so the linear-space math actually looks right on a monitor.

## Renders

| | |
|:--:|:--:|
| ![Diffuse + Metal](https://viniciusdugue.dev/projects/ray-tracing/img/diffuse-metal.png) | ![Diffuse + Metal + Fuzz](https://viniciusdugue.dev/projects/ray-tracing/img/diffuse-metal-fuzz.png) |
| Diffuse + Metal | Metal with fuzz factor |
| ![Dielectric](https://viniciusdugue.dev/projects/ray-tracing/img/dielectric-metal-diffuse.png) | ![Defocus blur](https://viniciusdugue.dev/projects/ray-tracing/img/defocus-blur.png) |
| Dielectric (glass) | Defocus blur (depth-of-field) |
| ![Low FOV](https://viniciusdugue.dev/projects/ray-tracing/img/low-fov.png) | ![High FOV](https://viniciusdugue.dev/projects/ray-tracing/img/high-fov.png) |
| Low vertical FOV | High vertical FOV |

[See the full progression on the project page →](https://viniciusdugue.dev/projects/ray-tracing/index.html)

## Output

The engine writes PPM images directly. View them with any image viewer that supports the format (or convert with ImageMagick).

## Reference

- *Ray Tracing in One Weekend* — Peter Shirley · [raytracing.github.io](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

---

<p align="center">
  <sub>
    More work at <a href="https://viniciusdugue.dev">viniciusdugue.dev</a>
  </sub>
</p>
