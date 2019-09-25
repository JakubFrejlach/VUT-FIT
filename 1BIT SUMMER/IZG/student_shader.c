/*!
 * @file
 * @brief This file contains implemenation of phong vertex and fragment shader.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <assert.h>
#include <math.h>

#include <student/gpu.h>
#include <student/student_shader.h>
#include <student/uniforms.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

/// \addtogroup shader_side Úkoly v shaderech
/// @{

void phong_vertexShader(GPUVertexShaderOutput *const      output,
                        GPUVertexShaderInput const *const input,
                        GPU const                         gpu) {
  /// \todo Naimplementujte vertex shader, který transformuje vstupní vrcholy do
  /// clip-space.<br>
  /// <b>Vstupy:</b><br>
  /// Vstupní vrchol by měl v nultém atributu obsahovat pozici vrcholu ve
  /// world-space (vec3) a v prvním
  /// atributu obsahovat normálu vrcholu ve world-space (vec3).<br>
  /// <b>Výstupy:</b><br>
  /// Výstupní vrchol by měl v nultém atributu obsahovat pozici vrcholu (vec3)
  /// ve world-space a v prvním
  /// atributu obsahovat normálu vrcholu ve world-space (vec3).
  /// Výstupní vrchol obsahuje pozici a normálu vrcholu proto, že chceme počítat
  /// osvětlení ve world-space ve fragment shaderu.<br>
  /// <b>Uniformy:</b><br>
  /// Vertex shader by měl pro transformaci využít uniformní proměnné obsahující
  /// view a projekční matici.
  /// View matici čtěte z uniformní proměnné "viewMatrix" a projekční matici
  /// čtěte z uniformní proměnné "projectionMatrix".
  /// Zachovejte jména uniformních proměnných a pozice vstupních a výstupních
  /// atributů.
  /// Pokud tak neučiníte, akceptační testy selžou.<br>
  /// <br>
  /// Využijte vektorové a maticové funkce.
  /// Nepředávajte si data do shaderu pomocí globálních proměnných.
  /// Pro získání dat atributů použijte příslušné funkce vs_interpret*
  /// definované v souboru program.h.
  /// Pro získání dat uniformních proměnných použijte příslušné funkce
  /// shader_interpretUniform* definované v souboru program.h.
  /// Vrchol v clip-space by měl být zapsán do proměnné gl_Position ve výstupní
  /// struktuře.<br>
  /// <b>Seznam funkcí, které jistě použijete</b>:
  ///  - gpu_getUniformsHandle()
  ///  - getUniformLocation()
  ///  - shader_interpretUniformAsMat4()
  ///  - vs_interpretInputVertexAttributeAsVec3()
  ///  - vs_interpretOutputVertexAttributeAsVec3()
  Mat4 const *const view = shader_interpretUniformAsMat4(gpu_getUniformsHandle(gpu), getUniformLocation(gpu, "viewMatrix"));
  Mat4 const *const proj = shader_interpretUniformAsMat4(gpu_getUniformsHandle(gpu), getUniformLocation(gpu, "projectionMatrix"));

  Vec3 const* const posIn = vs_interpretInputVertexAttributeAsVec3(gpu, input, 0);
  Vec3 const* const normalIn = vs_interpretInputVertexAttributeAsVec3(gpu, input, 1);


  // postup prevzat z triangleExample.c
  Mat4 mvp;
  multiply_Mat4_Mat4(&mvp, proj, view);

  Vec4 pos4;
  copy_Vec3Float_To_Vec4(&pos4, posIn, 1.f);

  multiply_Mat4_Vec4(&output->gl_Position, &mvp, &pos4);

  Vec3 *const posOut = vs_interpretOutputVertexAttributeAsVec3(gpu, output, 0);
  Vec3 *const normalOut = vs_interpretOutputVertexAttributeAsVec3(gpu, output, 1);


  init_Vec3(posOut, posIn->data[0], posIn->data[1], posIn->data[2]);
  init_Vec3(normalOut, normalIn->data[0], normalIn->data[1], normalIn->data[2]);

  
}

float clamping(float value, float n1, float n2) // Orezavani
{
	if (value < n2) {
		return max(value, n1);
	}

	return min(value, n2);
}
void phong_fragmentShader(GPUFragmentShaderOutput *const      output,
                          GPUFragmentShaderInput const *const input,
                          GPU const                           gpu) {
  /// \todo Naimplementujte fragment shader, který počítá phongův osvětlovací
  /// model s phongovým stínováním.<br>
  /// <b>Vstup:</b><br>
  /// Vstupní fragment by měl v nultém fragment atributu obsahovat
  /// interpolovanou pozici ve world-space a v prvním
  /// fragment atributu obsahovat interpolovanou normálu ve world-space.<br>
  /// <b>Výstup:</b><br>
  /// Barvu zapište do proměnné color ve výstupní struktuře.<br>
  /// <b>Uniformy:</b><br>
  /// Pozici kamery přečtěte z uniformní proměnné "cameraPosition" a pozici
  /// světla přečtěte z uniformní proměnné "lightPosition".
  /// Zachovejte jména uniformních proměnný.
  /// Pokud tak neučiníte, akceptační testy selžou.<br>
  /// <br>
  /// Dejte si pozor na velikost normálového vektoru, při lineární interpolaci v
  /// rasterizaci může dojít ke zkrácení.
  /// Zapište barvu do proměnné color ve výstupní struktuře.
  /// Shininess faktor nastavte na 40.f
  /// Difuzní barvu materiálu nastavte podle normály povrchu.
  /// V případě, že normála směřuje kolmo vzhůru je difuzní barva čistě bílá.
  /// V případě, že normála směřuje vodorovně nebo dolů je difuzní barva čiště zelená.
  /// Difuzní barvu spočtěte lineární interpolací zelené a bíle barvy pomocí interpolačního parameteru t.
  /// Interpolační parameter t spočtěte z y komponenty normály pomocí t = y*y (samozřejmě s ohledem na negativní čísla).
  /// Spekulární barvu materiálu nastavte na čistou bílou.
  /// Barvu světla nastavte na bílou.
  /// Nepoužívejte ambientní světlo.<br>
  /// <b>Seznam funkcí, které jistě využijete</b>:
  ///  - shader_interpretUniformAsVec3()
  ///  - fs_interpretInputAttributeAsVec3()
  (void)output;
  (void)input;
  (void)gpu;
  // ziskani atributu vstupniho fragmentu
  Vec3 const* pos = fs_interpretInputAttributeAsVec3(gpu, input, 0);
  Vec3 const* normal = fs_interpretInputAttributeAsVec3(gpu, input, 1);

  // ziskani uniformnich promennych
  Vec3 const* cameraPos = shader_interpretUniformAsVec3(gpu_getUniformsHandle(gpu), getUniformLocation(gpu, "cameraPosition"));
  Vec3 const* lightPos = shader_interpretUniformAsVec3(gpu_getUniformsHandle(gpu), getUniformLocation(gpu, "lightPosition"));

  float shininess = 40.f; // shininess faktor
  float t = normal->data[1] * normal->data[1]; // interpolacni parametr t
  Vec3 white; // vektor pro bilou barvou
  Vec3 green; // vektor pro zelenou barvou
  init_Vec3(&white, 1.f, 1.f, 1.f); // inicializace vektoru na bilou barvu
  init_Vec3(&green, 0.f, 1.f, 0.f); // inicializace vektoru na zelenou barvu

  Vec3 normalNormalize; // vektor pro normalizovanou normalu
  normalize_Vec3(&normalNormalize, normal); // normalizovani normaly

  Vec3 cameraRealPosNormalize; // vektor pro normalizovanou realnou pozici kamery
  sub_Vec3(&cameraRealPosNormalize, cameraPos, pos); // vypocet realne pozice kamery
  normalize_Vec3(&cameraRealPosNormalize, &cameraRealPosNormalize); // normalizace realne pozice kamery

  Vec3 lightRealPosNormalize; // vektor pro normalizovanou realnou pozici osvetleni
  sub_Vec3(&lightRealPosNormalize, lightPos, pos); // vypocet realne pozice osvetleni
  normalize_Vec3(&lightRealPosNormalize, &lightRealPosNormalize); // normalizace realne pozice osvetleni
  
  
  Vec3 Id; // vektor pro Lambertuv osvetlovaci model (slozka Phongova modelu)

  mix_Vec3(&Id, &green, &white, t); // linearni interpolace zelene a bile pomoci parametru t
  multiply_Vec3_Float(&Id, &Id, clamping(dot_Vec3(&normalNormalize, &lightRealPosNormalize), 0.f, 1.f)); // vypocet Lambertova osvetlovaciho modelu
  																									     // se svetlem neni nutno pocitat, protoze je nastaveno na bilou barvu

  Vec3 R; // slozka spektakularni slozky Phongova osvetlovaciho modelu
  Vec3 Is; // vektor pro spektakularni slozku Phongova osvetlovaciho modelu

  multiply_Vec3_Float(&R, &normalNormalize, 2 * clamping(dot_Vec3(&normalNormalize, &lightRealPosNormalize), 0.f, 1.f)); // vypocet R
  sub_Vec3(&R, &R, &lightRealPosNormalize); // vypocet R
  normalize_Vec3(&R, &R); // normalizace R
  multiply_Vec3_Float(&Is, &white, (float)pow(clamping(dot_Vec3(&cameraRealPosNormalize, &R), 0.f, 1.f), shininess)); // vypocet Is -> spektakularni barva je bila

  add_Vec3(&Id, &Id, &Is); // soucet Id a Is -> Phonguv osvetlovaci model
  copy_Vec3Float_To_Vec4(&output->color, &Id, 1.f); // Vysledna barva

}

/// @}