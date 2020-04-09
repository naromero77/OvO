program target_teams_distribute__parallel_for__simd

    implicit none

    REAL, ALLOCATABLE :: A(:)  
    REAL, ALLOCATABLE :: B(:)
  
    INTEGER :: L = 5
    INTEGER :: i
    INTEGER :: M = 6
    INTEGER :: j
    INTEGER :: N = 7
    INTEGER :: k

    INTEGER :: S
    S = L*M*N
     
    ALLOCATE(A(S), B(S) )
    CALL RANDOM_NUMBER(B)
  
    
    !$OMP TARGET TEAMS DISTRIBUTE   MAP(FROM: A) MAP(TO: B) 


    DO i = 1 , L 

    
    !$OMP PARALLEL DO 


    DO j = 1 , M 

    
    !$OMP SIMD 


    DO k = 1 , N 

    

    A( k + (j-1)*N + (i-1)*N*M ) = B( k + (j-1)*N + (i-1)*N*M )
 
     

    END DO

    !$OMP END SIMD
     

    END DO

    !$OMP END PARALLEL DO
     

    END DO

    !$OMP END TARGET TEAMS DISTRIBUTE
    

    IF (ANY(ABS(A - B) > EPSILON(A) )) THEN
        write(*,*)  'Wrong value', MAXVAL(ABS(A-B)), 'max difference'
        call exit(1)
    ENDIF

    DEALLOCATE(A,B)

end program target_teams_distribute__parallel_for__simd